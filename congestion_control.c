#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NOP 10

int arc4rand(int a){
    int rn = (arc4random()%10)%a;
    return rn == 0?1:rn;
}
int main(){
    int packet_sz[NOP],i,clk,b_size,o_rate,p_sz_rm=0,p_sz,p_time,op;
    for(i=0;i<NOP;i++){
        packet_sz[i] = arc4rand(6)*10;
    }
    for(i=0;i<NOP;i++){
        printf("\npacket[%d]:%d bytes",i,packet_sz[i]);
    }
    printf("Enter the output rate:");
    scanf("%d",&o_rate);
    printf("Enter the bucket size:");
    scanf("%d",&b_size);
    for(i=0;i<NOP;i++){
        if((packet_sz[i]+p_sz_rm)>b_size){
            if(packet_sz[i]>b_size){
                printf("\nIncoming packet size(%d bytes) is greater than the bucket size(%d bytes) - PACKET REJECTED.",packet_sz[i],b_size);
            }
            else{
                printf("\nBucket capcity exceeded - PACKET REJECTED.");
            }
        }
        else{
            p_sz_rm+=packet_sz[i];
            printf("\nIncoming packet size:%d",packet_sz[i]);
            printf("\nBytes remaining to transmit:%d",p_sz_rm);
            p_time=arc4rand(4)*10;
            printf("Time left to transmission:%d",p_time);
            for(clk=10;clk<p_time;clk+=10){
                sleep(1);
                if(p_sz_rm){
                    if(p_sz_rm<=o_rate){
                        op=p_sz_rm,p_sz_rm=0;
                    }
                    else{
                        op=o_rate,p_sz_rm-=o_rate;
                    }
                    printf("\npacket size of %d bytes is Tansmitted",op);
                    printf("\nBytes remaining to transmit:%d",p_sz_rm);
                }
                else{
                    printf("\nTime left for Transmission:%d units",p_time-clk);
                    printf("\nNo packets to Transmit.");
                }
            }
        }
    }
}
