import rclpy
from rclpy.node import Node
import time
from std_msgs.msg import Bool

class Scheduler(Node):

    def __init__(self):
        super().__init__('scheduler')
        self.enable_pub = self.create_publisher(Bool, '/enable', 10)
        time.sleep(2)
        timer_period = 0.01  # seconds
        self.timer = self.create_timer(timer_period, self.step)
        self.get_logger().info("Initialize Scheduler Node ...")
        self.keep_running = True

    def step(self):
        if self.keep_running:
            msg = Bool()
            msg.data = True
            self.enable_pub.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    scheduler = Scheduler()
    rclpy.spin(scheduler)
    scheduler.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()