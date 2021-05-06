// Copyright 2008 Willow Garage, Inc.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the Willow Garage, Inc. nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

/** \author Wim Meeussen */

#ifndef TF2_GEOMETRY_MSGS_H
#define TF2_GEOMETRY_MSGS_H

#include <tf2/convert.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2_ros/buffer_interface.h>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/quaternion_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <geometry_msgs/msg/wrench.hpp>
#include <geometry_msgs/msg/wrench_stamped.hpp>
#include <kdl/frames.hpp>

namespace tf2
{

/** \brief Convert a TransformStamped message to a KDL frame.
 * \param t TransformStamped message to convert.
 * \return The converted KDL Frame.
 */
inline
KDL::Frame gmTransformToKDL(const geometry_msgs::msg::TransformStamped& t)
  {
    return KDL::Frame(KDL::Rotation::Quaternion(t.transform.rotation.x, t.transform.rotation.y,
            t.transform.rotation.z, t.transform.rotation.w),
          KDL::Vector(t.transform.translation.x, t.transform.translation.y, t.transform.translation.z));
  }


/********************/
/** Vector3Stamped **/
/********************/

/** \brief Extract a timestamp from the header of a Vector message.
 * This function is a specialization of the getTimestamp template defined in tf2/convert.h.
 * \param t VectorStamped message to extract the timestamp from.
 * \return The timestamp of the message.
 */
template <>
inline
  tf2::TimePoint getTimestamp(const geometry_msgs::msg::Vector3Stamped& t) {return tf2_ros::fromMsg(t.header.stamp);}

/** \brief Extract a frame ID from the header of a Vector message.
 * This function is a specialization of the getFrameId template defined in tf2/convert.h.
 * \param t VectorStamped message to extract the frame ID from.
 * \return A string containing the frame ID of the message.
 */
template <>
inline
  std::string getFrameId(const geometry_msgs::msg::Vector3Stamped& t) {return t.header.frame_id;}

/** \brief Apply a geometry_msgs TransformStamped to an geometry_msgs Vector type.
  * This function is a specialization of the doTransform template defined in tf2/convert.h.
  * \param t_in The vector to transform, as a Vector3 message.
  * \param t_out The transformed vector, as a Vector3 message.
  * \param transform The timestamped transform to apply, as a TransformStamped message.
  */
  template <>
  inline
  void doTransform(const geometry_msgs::msg::Vector3& t_in, geometry_msgs::msg::Vector3& t_out, const geometry_msgs::msg::TransformStamped& transform)
  {
    KDL::Vector v_out = gmTransformToKDL(transform).M * KDL::Vector(t_in.x, t_in.y, t_in.z);
    t_out.x = v_out[0];
    t_out.y = v_out[1];
    t_out.z = v_out[2];
  }

/** \brief Apply a geometry_msgs TransformStamped to an geometry_msgs Vector type.
 * This function is a specialization of the doTransform template defined in tf2/convert.h.
 * \param t_in The vector to transform, as a timestamped Vector3 message.
 * \param t_out The transformed vector, as a timestamped Vector3 message.
 * \param transform The timestamped transform to apply, as a TransformStamped message.
 */
template <>
inline
  void doTransform(const geometry_msgs::msg::Vector3Stamped& t_in, geometry_msgs::msg::Vector3Stamped& t_out, const geometry_msgs::msg::TransformStamped& transform)
  {
//     KDL::Vector v_out = gmTransformToKDL(transform).M * KDL::Vector(t_in.vector.x, t_in.vector.y, t_in.vector.z);
//     t_out.vector.x = v_out[0];
//     t_out.vector.y = v_out[1];
//     t_out.vector.z = v_out[2];
    doTransform(t_in.vector, t_out.vector, transform);
    t_out.header.stamp = transform.header.stamp;
    t_out.header.frame_id = transform.header.frame_id;
  }

/** \brief Trivial "conversion" function for Vector3 message type.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param in A Vector3Stamped message.
 * \return The input argument.
 */
inline
geometry_msgs::msg::Vector3Stamped toMsg(const geometry_msgs::msg::Vector3Stamped& in)
{
  return in;
}

/** \brief Trivial "conversion" function for Vector3 message type.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param msg A Vector3Stamped message.
 * \param out The input argument.
 */
inline
void fromMsg(const geometry_msgs::msg::Vector3Stamped& msg, geometry_msgs::msg::Vector3Stamped& out)
{
  out = msg;
}



/******************/
/** PointStamped **/
/******************/

/** \brief Extract a timestamp from the header of a Point message.
 * This function is a specialization of the getTimestamp template defined in tf2/convert.h.
 * \param t PointStamped message to extract the timestamp from.
 * \return The timestamp of the message.
 */
template <>
inline
  tf2::TimePoint getTimestamp(const geometry_msgs::msg::PointStamped& t)  {return tf2_ros::fromMsg(t.header.stamp);}

/** \brief Extract a frame ID from the header of a Point message.
 * This function is a specialization of the getFrameId template defined in tf2/convert.h.
 * \param t PointStamped message to extract the frame ID from.
 * \return A string containing the frame ID of the message.
 */
template <>
inline
  std::string getFrameId(const geometry_msgs::msg::PointStamped& t)  {return t.header.frame_id;}

/** \brief Apply a geometry_msgs TransformStamped to an geometry_msgs Point type.
 * This function is a specialization of the doTransform template defined in tf2/convert.h.
 * \param t_in The point to transform, as a timestamped Point3 message.
 * \param t_out The transformed point, as a timestamped Point3 message.
 * \param transform The timestamped transform to apply, as a TransformStamped message.
 */
template <>
inline
  void doTransform(const geometry_msgs::msg::PointStamped& t_in, geometry_msgs::msg::PointStamped& t_out, const geometry_msgs::msg::TransformStamped& transform)
  {
    KDL::Vector v_out = gmTransformToKDL(transform) * KDL::Vector(t_in.point.x, t_in.point.y, t_in.point.z);
    t_out.point.x = v_out[0];
    t_out.point.y = v_out[1];
    t_out.point.z = v_out[2];
    t_out.header.stamp = transform.header.stamp;
    t_out.header.frame_id = transform.header.frame_id;
  }

/** \brief Trivial "conversion" function for Point message type.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param in A PointStamped message.
 * \return The input argument.
 */
inline
geometry_msgs::msg::PointStamped toMsg(const geometry_msgs::msg::PointStamped& in)
{
  return in;
}

/** \brief Trivial "conversion" function for Point message type.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param msg A PointStamped message.
 * \param out The input argument.
 */
inline
void fromMsg(const geometry_msgs::msg::PointStamped& msg, geometry_msgs::msg::PointStamped& out)
{
  out = msg;
}


/*****************/
/** PoseStamped **/
/*****************/

/** \brief Extract a timestamp from the header of a Pose message.
 * This function is a specialization of the getTimestamp template defined in tf2/convert.h.
 * \param t PoseStamped message to extract the timestamp from.
 * \return The timestamp of the message.
 */
template <>
inline
  tf2::TimePoint getTimestamp(const geometry_msgs::msg::PoseStamped& t)  {return tf2_ros::fromMsg(t.header.stamp);}

/** \brief Extract a frame ID from the header of a Pose message.
 * This function is a specialization of the getFrameId template defined in tf2/convert.h.
 * \param t PoseStamped message to extract the frame ID from.
 * \return A string containing the frame ID of the message.
 */
template <>
inline
  std::string getFrameId(const geometry_msgs::msg::PoseStamped& t)  {return t.header.frame_id;}

/** \brief Apply a geometry_msgs TransformStamped to an geometry_msgs Pose type.
 * This function is a specialization of the doTransform template defined in tf2/convert.h.
 * \param t_in The pose to transform, as a timestamped Pose3 message.
 * \param t_out The transformed pose, as a timestamped Pose3 message.
 * \param transform The timestamped transform to apply, as a TransformStamped message.
 */
template <>
inline
  void doTransform(const geometry_msgs::msg::PoseStamped& t_in, geometry_msgs::msg::PoseStamped& t_out, const geometry_msgs::msg::TransformStamped& transform)
  {
    KDL::Vector v(t_in.pose.position.x, t_in.pose.position.y, t_in.pose.position.z);
    KDL::Rotation r = KDL::Rotation::Quaternion(t_in.pose.orientation.x, t_in.pose.orientation.y, t_in.pose.orientation.z, t_in.pose.orientation.w);

    KDL::Frame v_out = gmTransformToKDL(transform) * KDL::Frame(r, v);
    t_out.pose.position.x = v_out.p[0];
    t_out.pose.position.y = v_out.p[1];
    t_out.pose.position.z = v_out.p[2];
    v_out.M.GetQuaternion(t_out.pose.orientation.x, t_out.pose.orientation.y, t_out.pose.orientation.z, t_out.pose.orientation.w);
    t_out.header.stamp = transform.header.stamp;
    t_out.header.frame_id = transform.header.frame_id;
  }

/** \brief Trivial "conversion" function for Pose message type.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param in A PoseStamped message.
 * \return The input argument.
 */
inline
geometry_msgs::msg::PoseStamped toMsg(const geometry_msgs::msg::PoseStamped& in)
{
  return in;
}

/** \brief Trivial "conversion" function for Pose message type.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param msg A PoseStamped message.
 * \param out The input argument.
 */
inline
void fromMsg(const geometry_msgs::msg::PoseStamped& msg, geometry_msgs::msg::PoseStamped& out)
{
  out = msg;
}


/*******************************/
/** PoseWithCovarianceStamped **/
/*******************************/

/** \brief Extract a timestamp from the header of a Pose message.
 * This function is a specialization of the getTimestamp template defined in tf2/convert.h.
 * \param t PoseWithCovarianceStamped message to extract the timestamp from.
 * \return The timestamp of the message.
 */
template <>
inline
  tf2::TimePoint getTimestamp(const geometry_msgs::msg::PoseWithCovarianceStamped& t)  {return tf2_ros::fromMsg(t.header.stamp);}

/** \brief Extract a frame ID from the header of a Pose message.
 * This function is a specialization of the getFrameId template defined in tf2/convert.h.
 * \param t PoseWithCovarianceStamped message to extract the frame ID from.
 * \return A string containing the frame ID of the message.
 */
template <>
inline
  std::string getFrameId(const geometry_msgs::msg::PoseWithCovarianceStamped& t)  {return t.header.frame_id;}

/** \brief Extract a covariance matrix from a PoseWithCovarianceStamped message.
 * This function is a specialization of the getCovarianceMatrix template defined in tf2/convert.h.
 * \param t PoseWithCovarianceStamped message to extract the covariance matrix from.
 * \return A nested-array representation of the covariance matrix from the message.
 */
template <>
inline
  std::array<std::array<double, 6>, 6> getCovarianceMatrix(const geometry_msgs::msg::PoseWithCovarianceStamped& t)  {return covarianceRowMajorToNested(t.pose.covariance);}

/** \author Wim Meeussen */

#ifndef TF2_GEOMETRY_MSGS__TF2_GEOMETRY_MSGS_H_
#define TF2_GEOMETRY_MSGS__TF2_GEOMETRY_MSGS_H_

#warning This header is obsolete, please include tf2_geometry_msgs/tf2_geometry_msgs.hpp instead

/**********************/
/*** WrenchStamped ****/
/**********************/

/** \brief Extract a timestamp from the header of a Wrench message.
 * This function is a specialization of the getTimestamp template defined in tf2/convert.h.
 * \param t WrenchStamped message to extract the timestamp from.
 * \return The timestamp of the message.
 */
template <>
inline
  tf2::TimePoint getTimestamp(const geometry_msgs::msg::WrenchStamped& t) {return tf2_ros::fromMsg(t.header.stamp);}

/** \brief Extract a frame ID from the header of a Wrench message.
 * This function is a specialization of the getFrameId template defined in tf2/convert.h.
 * \param t WrenchStamped message to extract the frame ID from.
 * \return A string containing the frame ID of the message.
 */
template <>
inline
  std::string getFrameId(const geometry_msgs::msg::WrenchStamped& t) {return t.header.frame_id;}


/** \brief Apply a geometry_msgs TransformStamped to an geometry_msgs Wrench type.
 * This function is a specialization of the doTransform template defined in tf2/convert.h.
 * \param t_in The wrench to transform, as a Wrench message.
 * \param t_out The transformed wrench, as a Wrench message.
 * \param transform The timestamped transform to apply, as a TransformStamped message.
 */
template<>
inline
  void doTransform(const geometry_msgs::msg::Wrench& t_in, geometry_msgs::msg::Wrench& t_out, const geometry_msgs::msg::TransformStamped& transform)
  {
    doTransform(t_in.force, t_out.force, transform);
    doTransform(t_in.torque, t_out.torque, transform);
  }

/** \brief Apply a geometry_msgs TransformStamped to an geometry_msgs WrenchStamped type.
 * This function is a specialization of the doTransform template defined in tf2/convert.h.
 * \param t_in The wrench to transform, as a timestamped Wrench message.
 * \param t_out The transformed wrench, as a timestamped Wrench message.
 * \param transform The timestamped transform to apply, as a TransformStamped message.
 */
template<>
inline
  void doTransform(const geometry_msgs::msg::WrenchStamped& t_in, geometry_msgs::msg::WrenchStamped& t_out, const geometry_msgs::msg::TransformStamped& transform)
  {
    doTransform(t_in.wrench, t_out.wrench, transform);
    t_out.header.stamp = transform.header.stamp;
    t_out.header.frame_id = transform.header.frame_id;
  }

/** \brief Trivial "conversion" function for Wrench message type.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param in A WrenchStamped message.
 * \return The input argument.
 */
inline
geometry_msgs::msg::WrenchStamped toMsg(const geometry_msgs::msg::WrenchStamped& in)
{
  return in;
}

/** \brief Trivial "conversion" function for Wrench message type.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param msg A WrenchStamped message.
 * \param out The input argument.
 */
inline
void fromMsg(const geometry_msgs::msg::WrenchStamped& msg, geometry_msgs::msg::WrenchStamped& out)
{
  out = msg;
}

/** \brief Convert as stamped tf2 Array with 2 Vector3 type to its equivalent geometry_msgs representation.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param in A instance of the tf2::Stamped<std::array<tf2::Vector3, 2>> specialization of the tf2::Stamped template.
 * \return The WrenchStamped converted to a geometry_msgs WrenchStamped message type.
 */
// inline
// geometry_msgs::msg::WrenchStamped toMsg(const tf2::Stamped<std::array<tf2::Vector3, 2>>& in)
// {
//   geometry_msgs::msg::WrenchStamped out;
//   out.header.stamp = tf2_ros::toMsg(in.stamp_);
//   out.header.frame_id = in.frame_id_;
//   out.wrench.force = toMsg(in[0]);
//   out.wrench.torque = toMsg(in[1]);
//   return out;
// }

/** \brief Convert a WrenchStamped message to its equivalent tf2 representation.
 * This function is a specialization of the toMsg template defined in tf2/convert.h.
 * \param in A WrenchStamped message type.
 * \param out The WrenchStamped converted to the equivalent tf2 type.
 */
// inline
// void fromMsg(const geometry_msgs::msg::WrenchStamped& in, tf2::Stamped<std::array<tf2::Vector3, 2>>& out)
// {
//   out.stamp_ = tf2_ros::fromMsg(in.header.stamp);
//   out.frame_id_ = in.header.frame_id;
//   tf2::Vector3 tmp;
//   fromMsg(in.wrench.force, tmp);
//   tf2::Vector3 tmp1;
//   fromMsg(in.wrench.torque, tmp1);
//   std::array<tf2::Vector3, 2> tmp_array;
//   tmp_array[0] = tmp;
//   tmp_array[1] = tmp1;
//   out.setData(tmp_array);
// }

} // namespace

#endif  // TF2_GEOMETRY_MSGS__TF2_GEOMETRY_MSGS_H_
