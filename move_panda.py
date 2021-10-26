#! usr/bin/env python3

import os

import sys
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
from math import pi
import copy
import std_msgs.msg
from franka_gripper.msg import MoveActionGoal
from franka_msgs.msg import FrankaState

from time import sleep


height_block = .02
width_block  = .02


y_position  = 0
x_positions = [.35, .37, .39]#.31 -- .54
z_base      = .11
z_up        = .20

def getActions():
    os.system("clingo toAsp.lp | tail -10 | head -1 > actions.txt")
    actions = open("actions.txt", "r")
    r=actions.readlines()[0]
    print(r)
    lista = r.split(" ")
    actionList = []
    for action in lista:
        if "noop" in action:
            continue
        actiontype = "pick" if action.find("pick")!=-1 else "put"
        argumentsI = action.rfind("(")
        argumentsF = action.find(")")
        arguments  = [actiontype]+list(action[argumentsI: argumentsF+1])
        arguments.remove("(")
        arguments.remove(")")
        arguments.remove(",")
        arguments.remove(",")
        actionList.append(arguments)
    return actionList

def execute_actions(move_group, pub, display_trajectory_publisher, actions):

    for action in actions:
        print(action)
        print("move left/right")
        current_pose = move_group.get_current_pose().pose
        move_robot(move_group, display_trajectory_publisher, action)
        if(current_pose==move_group.get_current_pose().pose):
            raise ValueError("error")
        print(move_group.get_current_pose().pose)
        sleep(2)
        print("let down")
        current_pose = move_group.get_current_pose().pose
        let_down(move_group, display_trajectory_publisher, action)
        if(current_pose==move_group.get_current_pose().pose):
            raise ValueError("error")
        print(move_group.get_current_pose().pose)
        sleep(2)
        print("move gripper")
        current_pose = move_group.get_current_pose().pose
        move_gripper(pub, action[3])
        sleep(2)
        print("raise up")
        current_pose = move_group.get_current_pose().pose
        raise_up(move_group, display_trajectory_publisher)
        if(current_pose==move_group.get_current_pose().pose):
            raise ValueError("error")
        print(move_group.get_current_pose().pose)
        sleep(2)

def raise_up(move_group, display_trajectory_publisher):

    waypoints = []

    wpose = move_group.get_current_pose().pose
    wpose.position.z = z_up

    waypoints.append(copy.deepcopy(wpose))

    (plan, fraction) = move_group.compute_cartesian_path(
                                       waypoints,   # waypoints to follow
                                       0.01,        # eef_step
                                       0.0)         # jump_threshold

    display_trajectory = moveit_msgs.msg.DisplayTrajectory()
    display_trajectory.trajectory_start = robot.get_current_state()
    display_trajectory.trajectory.append(plan)
    # Publish
    display_trajectory_publisher.publish(display_trajectory)

    move_group.execute(plan, wait=True)

def let_down(move_group, display_trajectory_publisher, action):

    waypoints = []

    wpose = move_group.get_current_pose().pose
    wpose.position.z = (int(action[3])-1)*height_block + z_base

    waypoints.append(copy.deepcopy(wpose))

    (plan, fraction) = move_group.compute_cartesian_path(
                                       waypoints,   # waypoints to follow
                                       0.01,        # eef_step
                                       0.0)         # jump_threshold

    display_trajectory = moveit_msgs.msg.DisplayTrajectory()
    display_trajectory.trajectory_start = robot.get_current_state()
    display_trajectory.trajectory.append(plan)
    # Publish
    display_trajectory_publisher.publish(display_trajectory)

    move_group.execute(plan, wait=True)

    """
    pose_goal = move_group.get_current_pose().pose

    pose_goal.position.z = (int(action[3])-1)*height_block + z_base

    move_group.set_pose_target(pose_goal)
    plan = move_group.go(wait=True)
    move_group.stop()
    move_group.clear_pose_targets()
    current_pose = move_group.get_current_pose().pose
    """

def go_to_init_goal(move_group, display_trajectory_publisher):
    waypoints = []
    pose_goal = move_group.get_current_pose().pose
    pose_goal.orientation.x = 0.923955699469
    pose_goal.orientation.y = -0.382499497279
    pose_goal.orientation.z = 1.3249325839e-12
    pose_goal.orientation.w = 3.20041176635e-12
    pose_goal.position.x = x_positions[1]
    pose_goal.position.y = 0
    pose_goal.position.z = z_up
    waypoints.append(copy.deepcopy(pose_goal))
    (plan, fraction) = move_group.compute_cartesian_path(
                                       waypoints,   # waypoints to follow
                                       0.01,        # eef_step
                                       0.0)         # jump_threshold

    display_trajectory = moveit_msgs.msg.DisplayTrajectory()
    display_trajectory.trajectory_start = robot.get_current_state()
    display_trajectory.trajectory.append(plan)
    # Publish
    display_trajectory_publisher.publish(display_trajectory)

    move_group.execute(plan, wait=True)


def move_robot(move_group, display_trajectory_publisher, action):

    waypoints = []

    wpose = move_group.get_current_pose().pose

    wpose.position.x = x_positions[int(action[3])-1]

    waypoints.append(copy.deepcopy(wpose))

    (plan, fraction) = move_group.compute_cartesian_path(
                                       waypoints,   # waypoints to follow
                                       0.01,        # eef_step
                                       0.0)         # jump_threshold

    display_trajectory = moveit_msgs.msg.DisplayTrajectory()
    display_trajectory.trajectory_start = robot.get_current_state()
    display_trajectory.trajectory.append(plan)
    # Publish
    display_trajectory_publisher.publish(display_trajectory)

    move_group.execute(plan, wait=True)



def move_gripper(pub, type_action):
    
    command=MoveActionGoal()
    command.goal.width=.08 if type_action=="put" else width_block
    command.goal.speed=.1
    rospy.loginfo(command)
    pub.publish(command)
        

if __name__ == "__main__":
    l=getActions()
    moveit_commander.roscpp_initialize(sys.argv)
    rospy.init_node('move_group_python_interface', anonymous=True)

    robot = moveit_commander.RobotCommander()

    scene = moveit_commander.PlanningSceneInterface()

    group_name = "panda_arm"
    move_group = moveit_commander.MoveGroupCommander(group_name)

    print("before table")
    box_pose = geometry_msgs.msg.PoseStamped()
    box_pose.header.frame_id = "panda_leftfinger"
    box_pose.pose.position.z = 0
    box_pose.pose.position.x = 0
    box_name = "table"
    scene.add_box(box_name, box_pose, size=(3, 3, .02))
    print("after table")

    display_trajectory_publisher = rospy.Publisher('/move_group/display_planned_path',
                                               moveit_msgs.msg.DisplayTrajectory,
                                               queue_size=20)

    pub = rospy.Publisher('franka_gripper/move/goal', MoveActionGoal, queue_size=10)
    print("got to starting position")
    go_to_init_goal(move_group, display_trajectory_publisher)
    execute_actions(move_group, pub, display_trajectory_publisher, l)
    print("got to starting position")
    go_to_init_goal(move_group, display_trajectory_publisher)




"""
def raise_up(move_group):
    pose_goal = move_group.get_current_pose().pose
    pose_goal.position.z = z_up
    move_group.set_pose_target(pose_goal)
    plan = move_group.go(wait=True)
    move_group.stop()
    move_group.clear_pose_targets()
    current_pose = move_group.get_current_pose().pose


def let_down(move_group, action):
    pose_goal = move_group.get_current_pose().pose

    valy=y_position[int(action[3])-1]

    pose_goal.position.z = 0.04+(int(action[3])-1)*height_block+z_up

    move_group.set_pose_target(pose_goal)
    plan = move_group.go(wait=True)
    move_group.stop()
    move_group.clear_pose_targets()
    current_pose = move_group.get_current_pose().pose


def move_robot(move_group, action):
    pose_goal = move_group.get_current_pose().pose

    valy=y_position[int(action[3])-1]

    pose_goal.position.y = valy
    
    move_group.set_pose_target(pose_goal)

    plan = move_group.go(wait=True)
    move_group.stop()
    move_group.clear_pose_targets()

    current_pose = move_group.get_current_pose().pose
    return (pose_goal, current_pose, 0.01)
"""