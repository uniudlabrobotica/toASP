#! usr/bin/env python3

import os

import sys
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg
from math import pi

import std_msgs.msg
from franka_gripper.msg import MoveActionGoal
from franka_msgs.msg import FrankaState

from time import sleep


height_block=.02
width_block=.02
z_base=.082

#x_position=[.54, .54, .54]
#y_position=[-.27, -.03, .24]

central_position=[2.09, -1.16, -2.11, -2, -1.33, 2.20, -1.68]
base_joint=[2.6, 2.10, 2.14]


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

def execute_actions(move_group, pub, actions):

    for action in actions:
        
        #go_to_init_goal(move_group)
        #go_to_pose_goal(move_group, action)
        move_robot(move_group, action)
        sleep(2)
        move_gripper(pub, action[3])


def go_to_init_goal(move_group):
    pose_goal = geometry_msgs.msg.Pose()
    pose_goal.orientation.w = 0.0227707401509
    pose_goal.orientation.x = 0.383262744613
    pose_goal.orientation.y = 0.923320337876
    pose_goal.orientation.z = 0.00840925977722
    pose_goal.position.x = .5
    pose_goal.position.y = 0
    pose_goal.position.z = .5

    move_group.set_pose_target(pose_goal)

    plan = move_group.go(wait=True)
    move_group.stop()
    move_group.clear_pose_targets()

    current_pose = move_group.get_current_pose().pose
    return (pose_goal, current_pose, 0.01)

def move_robot(move_group, action):

    joint_goal = move_group.get_current_joint_values()
    joint_goal=[2.09, -1.16, -2.11, -2, -1.33, 2.20, -1.68]
    val=0
    if int(action[3])==1:
        val=-.08
    elif int(action[3])==2:
        val=-.08
    else :
        val=.08
    joint_goal[0] = joint_goal[0]+val
    move_group.go(joint_goal, wait=True)
    move_group.stop()
    current_joints = move_group.get_current_joint_values()

def go_to_pose_goal(move_group, action):

    current_pose = move_group.get_current_pose().pose
    pose_goal = geometry_msgs.msg.Pose()
    print(action)
    pose_goal.position.x = x_position[int(action[3])-1]
    pose_goal.position.y = y_position[int(action[3])-1]
    pose_goal.position.z = 0.02+z_base+(int(action[2])-1)*height_block

    move_group.set_pose_target(pose_goal)

    plan = move_group.go(wait=True)
    move_group.stop()
    move_group.clear_pose_targets()

    current_pose = move_group.get_current_pose().pose
    return (pose_goal, current_pose, 0.01)

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

    pub = rospy.Publisher('franka_gripper/move/goal', MoveActionGoal, queue_size=10)
    go_to_init_goal(move_group)
    execute_actions(move_group, pub, l)


"""
  x: 0.54522191883
  y: -0.0316979921766
  z: 0.0836985635194
"""


"""
[2.09, -1.16, -2.11, -2, -1.33, 2.20, -1.68]
"""