import math
import pybullet as p
from time import sleep
from control import jointsPosition

# Instanciation de Bullet
physicsClient = p.connect(p.GUI)
p.setGravity(0, 0, -10)

# Chargement du sol
planeId = p.loadURDF('plane.urdf')

# Chargement du robot
cubeStartPos = [0, 0, 0.1]
cubeStartOrientation = p.getQuaternionFromEuler([0, 0, 0])
quadruped = p.loadURDF("./quadruped/robot.urdf",
                       cubeStartPos, cubeStartOrientation)
cubePos, cubeOrn = p.getBasePositionAndOrientation(quadruped)

# Map des joints
jointsMap = [0, 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14]
t = 0
dt = 0.01
p.setPhysicsEngineParameter(fixedTimeStep=dt)

while True:
    t += dt
    joints = jointsPosition(t)
    for k in range(len(joints)):
        jointInfo = p.getJointInfo(quadruped, jointsMap[k])
        p.setJointMotorControl2(quadruped, jointInfo[0], p.POSITION_CONTROL, joints[k])
    p.stepSimulation()
    sleep(dt)
