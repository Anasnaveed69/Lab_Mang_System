# Lab 12 NS-3 Script (Clean Minimal Version)

import ns.applications as apps
import ns.core as core
import ns.internet as inet
import ns.network as network
import ns.point_to_point as p2p
import ns.flow_monitor as flowmon
import ns.netanim as netanim

SIM_STOP_TIME = 5.0
TCP_PORT = 50000
UDP_PORT = 40000

UDP_PACKET_SIZE = 1024
UDP_PKT_RATE = 100.0
UDP_INTERVAL = 1.0 / UDP_PKT_RATE

nodes = network.NodeContainer()
nodes.Create(4)
n0, n1, n2, n3 = nodes.Get(0), nodes.Get(1), nodes.Get(2), nodes.Get(3)

p2p_2mb_10ms = p2p.PointToPointHelper()
p2p_2mb_10ms.SetDeviceAttribute("DataRate", core.StringValue("2Mbps"))
p2p_2mb_10ms.SetChannelAttribute("Delay", core.StringValue("10ms"))
p2p_2mb_10ms.SetQueue("ns3::DropTailQueue", "MaxPackets", core.UintegerValue(10))

p2p_17mb_20ms = p2p.PointToPointHelper()
p2p_17mb_20ms.SetDeviceAttribute("DataRate", core.StringValue("1.7Mbps"))
p2p_17mb_20ms.SetChannelAttribute("Delay", core.StringValue("20ms"))
p2p_17mb_20ms.SetQueue("ns3::DropTailQueue", "MaxPackets", core.UintegerValue(10))

dev_n0_n2 = p2p_2mb_10ms.Install(n0, n2)
dev_n1_n2 = p2p_2mb_10ms.Install(n1, n2)
dev_n2_n3 = p2p_17mb_20ms.Install(n2, n3)

stack = inet.InternetStackHelper()
stack.Install(nodes)

addr = inet.Ipv4AddressHelper()
addr.SetBase("10.1.1.0", "255.255.255.0")
ifaces_n0_n2 = addr.Assign(dev_n0_n2)

addr.SetBase("10.1.2.0", "255.255.255.0")
ifaces_n1_n2 = addr.Assign(dev_n1_n2)

addr.SetBase("10.1.3.0", "255.255.255.0")
ifaces_n2_n3 = addr.Assign(dev_n2_n3)

# TCP: n1 → n3
packet_sink_helper = apps.PacketSinkHelper(
    "ns3::TcpSocketFactory",
    inet.InetSocketAddress(inet.Ipv4Address.GetAny(), TCP_PORT)
)
sink_app = packet_sink_helper.Install(n3)
sink_app.Start(core.Seconds(0.0))
sink_app.Stop(core.Seconds(SIM_STOP_TIME))

n3_addr = ifaces_n2_n3.GetAddress(1)
bulk_sender = apps.BulkSendHelper(
    "ns3::TcpSocketFactory",
    inet.InetSocketAddress(n3_addr, TCP_PORT)
)
bulk_sender.SetAttribute("MaxBytes", core.UintegerValue(0))
tcp_sender_app = bulk_sender.Install(n1)
tcp_sender_app.Start(core.Seconds(0.5))
tcp_sender_app.Stop(core.Seconds(4.0))

# UDP: n0 → n3
udp_server = apps.UdpServerHelper(UDP_PORT)
server_apps = udp_server.Install(n3)
server_apps.Start(core.Seconds(0.0))
server_apps.Stop(core.Seconds(SIM_STOP_TIME))

udp_client = apps.UdpClientHelper(n3_addr, UDP_PORT)
udp_client.SetAttribute("MaxPackets", core.UintegerValue(0))
udp_client.SetAttribute("Interval", core.TimeValue(core.Seconds(UDP_INTERVAL)))
udp_client.SetAttribute("PacketSize", core.UintegerValue(UDP_PACKET_SIZE))

client_apps = udp_client.Install(n0)
client_apps.Start(core.Seconds(0.1))
client_apps.Stop(core.Seconds(4.5))

p2p_2mb_10ms.EnablePcapAll("lab12_p2p_2mb_10ms")
p2p_17mb_20ms.EnablePcapAll("lab12_p2p_17mb_20ms")

fm_helper = flowmon.FlowMonitorHelper()
monitor = fm_helper.InstallAll()

anim = netanim.AnimationInterface("lab12_netanim.xml")
anim.EnablePacketMetadata()
anim.SetConstantPosition(n0, 0.0, 50.0)
anim.SetConstantPosition(n1, 0.0, 150.0)
anim.SetConstantPosition(n2, 200.0, 100.0)
anim.SetConstantPosition(n3, 400.0, 100.0)

core.Simulator.Stop(core.Seconds(SIM_STOP_TIME))
core.Simulator.Run()

monitor.CheckForLostPackets()
classifier = fm_helper.GetClassifier()

print("\nFlowMonitor results:")
for flow_id, stats in monitor.GetFlowStats().items():
    t = classifier.FindFlow(flow_id)
    proto = "UDP" if t.protocol == inet.UdpSocketFactory.GetTypeId().GetName() else "TCP"
    thr = (stats.rxBytes * 8.0) / (SIM_STOP_TIME * 1e6)
    print(f"Flow {flow_id}: {t.sourceAddress} -> {t.destinationAddress} [{proto}] "
          f"Tx={stats.txBytes} Rx={stats.rxBytes} Throughput={thr:.4f} Mbps")

core.Simulator.Destroy()
print("Simulation done. NetAnim: lab12_netanim.xml")
