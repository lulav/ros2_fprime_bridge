// ======================================================================
// \title  controller_comp.hpp
// \author dev
// \brief  hpp file for controller_comp component implementation class
// ======================================================================

#ifndef controller_comp_HPP
#define controller_comp_HPP

#include "spring/controller/controller_compComponentAc.hpp"

#include "../../../examples/spring_mass_dumper/include/controller.hpp"

namespace spring {

  class controller_comp :
    public controller_compComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object controller_comp
      //!
      controller_comp(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object controller_comp
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object controller_comp
      //!
      ~controller_comp();

    private:
      Controller _controller;

      void copy_to_controller_input(const spring::state &state_input,
                                    ::state controller_input);
                                    
      void copy_from_controller_output(const ::control_signal& controller_output,
                                       spring::control_signal& dynamics_input);

      void write_telemetry(const spring::control_signal& dynamics_input);

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
