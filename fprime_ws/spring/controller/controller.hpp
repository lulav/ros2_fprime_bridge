// ======================================================================
// \title  controller.hpp
// \author dev
// \brief  hpp file for controller component implementation class
// ======================================================================

#ifndef controller_HPP
#define controller_HPP

#include "spring/controller/controllerComponentAc.hpp"

namespace spring {

  class controller :
    public controllerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object controller
      //!
      controller(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object controller
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object controller
      //!
      ~controller();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for state_in
      //!
      void state_in_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const spring::state &state_input /*!< 
      input from dynamics
      */
      );


    };

} // end namespace spring

#endif
