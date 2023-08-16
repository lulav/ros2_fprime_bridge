module spring {

  # ----------------------------------------------------------------------
  # Symbolic constants for port numbers
  # ----------------------------------------------------------------------

    enum Ports_RateGroups {
      rateGroup1
    # rateGroup2
    # rateGroup3
    }

    enum Ports_StaticMemory {
      downlink
      uplink
    }

  topology spring {

    # ----------------------------------------------------------------------
    # Instances used in the topology
    # ----------------------------------------------------------------------

    instance $health
    instance blockDrv
    instance chanTlm
    instance cmdDisp
    instance cmdSeq
    instance comm
    instance downlink
    instance eventLogger
    instance fatalAdapter
    instance fatalHandler
    instance fileDownlink
    instance fileManager
    instance fileUplink
    instance fileUplinkBufferManager
    instance linuxTime
    #instance prmDb
    instance rateGroup1Comp
    instance rateGroupDriverComp
    instance staticMemory
    instance textLogger
    instance uplink
    instance systemResources
    # project instances
    instance the_controller
    instance the_bridge

    # ----------------------------------------------------------------------
    # Pattern graph specifiers
    # ----------------------------------------------------------------------

    command connections instance cmdDisp

    event connections instance eventLogger

#    param connections instance prmDb

    telemetry connections instance chanTlm

    text event connections instance textLogger

    time connections instance linuxTime

    health connections instance $health

    # ----------------------------------------------------------------------
    # Direct graph specifiers
    # ----------------------------------------------------------------------

    connections Downlink {

      chanTlm.PktSend -> downlink.comIn
      eventLogger.PktSend -> downlink.comIn
      fileDownlink.bufferSendOut -> downlink.bufferIn

      downlink.framedAllocate -> staticMemory.bufferAllocate[Ports_StaticMemory.downlink]
      downlink.framedOut -> comm.send
      downlink.bufferDeallocate -> fileDownlink.bufferReturn

      comm.deallocate -> staticMemory.bufferDeallocate[Ports_StaticMemory.downlink]

    }

    connections FaultProtection {
      eventLogger.FatalAnnounce -> fatalHandler.FatalReceive
    }

    connections RateGroups {

      # Block driver
      blockDrv.CycleOut -> rateGroupDriverComp.CycleIn

      # Rate group 1 - @ 1Hz
      rateGroupDriverComp.CycleOut[Ports_RateGroups.rateGroup1] -> rateGroup1Comp.CycleIn
      rateGroup1Comp.RateGroupMemberOut[0] -> chanTlm.Run
      rateGroup1Comp.RateGroupMemberOut[1] -> fileDownlink.Run
      rateGroup1Comp.RateGroupMemberOut[2] -> systemResources.run
      rateGroup1Comp.RateGroupMemberOut[3] -> cmdSeq.schedIn
      rateGroup1Comp.RateGroupMemberOut[4] -> $health.Run
      rateGroup1Comp.RateGroupMemberOut[5] -> fileUplinkBufferManager.schedIn
    }

    connections Sequencer {
      cmdSeq.comCmdOut -> cmdDisp.seqCmdBuff
      cmdDisp.seqCmdStatus -> cmdSeq.cmdResponseIn
    }

    connections Uplink {

      comm.allocate -> staticMemory.bufferAllocate[Ports_StaticMemory.uplink]
      comm.$recv -> uplink.framedIn
      uplink.framedDeallocate -> staticMemory.bufferDeallocate[Ports_StaticMemory.uplink]

      uplink.comOut -> cmdDisp.seqCmdBuff
      cmdDisp.seqCmdStatus -> uplink.cmdResponseIn

      uplink.bufferAllocate -> fileUplinkBufferManager.bufferGetCallee
      uplink.bufferOut -> fileUplink.bufferSendIn
      uplink.bufferDeallocate -> fileUplinkBufferManager.bufferSendIn
      fileUplink.bufferSendOut -> fileUplinkBufferManager.bufferSendIn

    }

    connections spring_connections {
      the_bridge.state_out -> the_controller.state_in
      the_controller.control_out -> the_bridge.control_in
    }

  }

}
