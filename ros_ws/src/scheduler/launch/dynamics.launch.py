from launch import LaunchDescription
import sys
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from ament_index_python.packages import get_package_share_directory
import launch
import os
dynamics_config = os.path.join(
    get_package_share_directory('dynamics_node'),
    'config',
    'params.yaml'
    )

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='dynamics_node',
            executable='dynamics',
            name='dynamics',
            output='screen',
            parameters = [dynamics_config]
        ),
        Node(
            package='ros2_udp_bridge',
            executable='bridge',
            name='bridge',
            output='screen',
        ),
        Node(
            package='scheduler',
            executable='scheduler',
            name='scheduler',
            output='screen'
        )
    ])