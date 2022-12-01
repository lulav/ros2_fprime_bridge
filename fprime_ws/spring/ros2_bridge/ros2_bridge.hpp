// ======================================================================
// \title  ros2_bridge.hpp
// \author dev
// \brief  hpp file for ros2_bridge component implementation class
// ======================================================================

#ifndef ros2_bridge_HPP
#define ros2_bridge_HPP

#include "spring/ros2_bridge/ros2_bridgeComponentAc.hpp"

namespace spring {

  class ros2_bridge :
    public ros2_bridgeComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ros2_bridge
      //!
      ros2_bridge(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ros2_bridge
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ros2_bridge
      //!
      ~ros2_bridge();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for control_in
      //!
      void control_in_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const spring::control_signal &control_output /*!< 
      output from controller
      */
      );


    };

} // end namespace spring

#endif
