import random
import time

NOF_PACKETS = 10
def arc4rand(a):
    rn = (random.randint(0, 2**31 - 1) % 10) % a
    return 1 if rn == 0 else rn
def main():
    packet_sz = [0] * NOF_PACKETS
    p_sz_rm = 0
    p_sz = 0
    for i in range(NOF_PACKETS):
        packet_sz[i] = arc4rand(6) * 10
    for i in range(NOF_PACKETS):
        print(f"packet[{i}]: {packet_sz[i]} bytes")
    o_rate = int(input("\nEnter the Output rate: "))
    b_size = int(input("Enter the Bucket Size: "))
    for i in range(NOF_PACKETS):
        if (packet_sz[i] + p_sz_rm) > b_size:
            if packet_sz[i] > b_size:
                print(
                    f"\n\nIncoming packet size ({packet_sz[i]}bytes) is Greater than bucket capacity ({b_size}bytes)-PACKET REJECTED"
                )
            else:
                print("\n\nBucket capacity exceeded-PACKETS REJECTED!!")
        else:
            p_sz += packet_sz[i]
            p_sz_rm += packet_sz[i]
            print(f"\n\nIncoming Packet size: {packet_sz[i]}")
            print(f"Bytes remaining to Transmit: {p_sz_rm}")

            p_time = arc4rand(4) * 10
            print(f"Time left for transmission: {p_time} units")
            for clk in range(10, p_time + 1, 10):
                time.sleep(1)
                if p_sz_rm > 0:
                    if p_sz_rm <= o_rate:
                        op = p_sz_rm
                        p_sz_rm = 0
                    else:
                        op = o_rate
                        p_sz_rm -= o_rate
                    print(
                        f" Packet of size {op} Transmitted---Bytes Remaining to Transmit:{p_sz_rm}"
                    )
                else:
                    print(f" Time left for transmission {p_time - clk} units")
                    print("No packets to transmit")
if __name__ == "__main__":
    main()   