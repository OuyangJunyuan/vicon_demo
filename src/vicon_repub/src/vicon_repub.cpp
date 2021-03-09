#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
/*
geometry_msgs/TransformStamped

std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
string child_frame_id
geometry_msgs/Transform transform
  geometry_msgs/Vector3 translation
    float64 x
    float64 y
    float64 z
  geometry_msgs/Quaternion rotation
    float64 x
    float64 y
    float64 z
    float64 w
*/
/*
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
string child_frame_id
geometry_msgs/PoseWithCovariance pose
  geometry_msgs/Pose pose
    geometry_msgs/Point position
      float64 x
      float64 y
      float64 z
    geometry_msgs/Quaternion orientation
      float64 x
      float64 y
      float64 z
      float64 w
  float64[36] covariance
geometry_msgs/TwistWithCovariance twist
  geometry_msgs/Twist twist
    geometry_msgs/Vector3 linear
      float64 x
      float64 y
      float64 z
    geometry_msgs/Vector3 angular
      float64 x
      float64 y
      float64 z
  float64[36] covariance
*/

ros::Publisher odom_pub;

void vicon_callback(const geometry_msgs::TransformStamped::ConstPtr & msg){
	nav_msgs::Odometry odom_;
	odom_.pose.pose.position.x = msg-> transform. translation.x;
	odom_.pose.pose.position.y = msg-> transform. translation.y;
	odom_.pose.pose.position.z = msg-> transform. translation.z;
	
	odom_.pose.pose.orientation = msg-> transform.rotation;
	odom_.header.stamp = ros::Time::now();
	odom_.header.frame_id = "world";
	odom_pub.publish(odom_);
	
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "vicon_repub");
	ros::NodeHandle nh("~");
	ros::Subscriber vicon_sub = nh.subscribe<geometry_msgs::TransformStamped>("/vicon/vehicle1/vehicle1", 1, vicon_callback);
	
	odom_pub = nh.advertise<nav_msgs::Odometry>("/Vehicle",1);
	ros::spin();
}
