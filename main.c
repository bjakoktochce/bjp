/* 
 * Copyright (c) 2016, 2017 Bartosz Jakoktochce <grypsy@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the <organization>.
 * 4. Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <netinet/ip.h> 
#include <ncurses.h>

#include <getopt.h>
//#include "tcp.h"

#include "version.h"

/*
 * Print usage of the program
 * when no or bad options were set
 */

int 
usage(void)
{
        printw("bjp %s small ping utility by Bartosz Jakoktochce\n\n",VERSION);
	printw("usage: bjp <protocol> <flags> <address> \n\n");
	printw("protocol:\n");
        printw("        -t TCP packet\n");
        printw("        -i ICMP packet\n");
	printw("flags:\n");
        printw("        -S SYN flag\n");
	printw("	-F FIN flag\n");
        printw("        -A ACK flag\n");
        printw("        -R RST flag\n");
	printw("	-U URG flag\n");
	printw("	-P PSH flag\n");
	printw("options:\n");	
        printw("	-p destination port\n");
	printw("	-s packet size\n");
	
	printw("\n");
	refresh();
	getch();
	endwin();
	return 0;
}

/*
 * Main loop of the program
 *
 */

int 
main (int argc, char *argv[])
{
	int opt = 0;

	initscr();

	//Datagram to represent the packet
    	char datagram[4096] , source_ip[32] , *data , *pseudogram;
     
    	//zero out the packet buffer
    	memset (datagram, 0, 4096);
     
    	//IP header
    	struct iphdr *iph = (struct iphdr *) datagram;
     
    	//TCP header
    	struct tcphdr *tcph = (struct tcphdr *) (datagram + sizeof (struct ip));


	/*
	 * check arguments from command line
	 */
	
	while ((opt = getopt(argc, argv, "itSARFUP")) != -1) {
               switch (opt) {
               		case 'i':
                   		break;
               		case 't':
                   		break;
			case 'p':
				break;
			case 's':
				break;
			case 'S':
				tcph->syn = 1;
				break;
			case 'A':
                                tcph->ack = 1;
				break;
			case 'R':
                                tcph->rst = 1;
				break;
			case 'F':
				tcph->fin = 1;
				break;
			case 'U':
				break;
			case 'P':
				break;
			default: 
				;
				break;
				//fprintf(stderr, "test");
				//usage();
				//exit(EXIT_FAILURE);
               }
        }

	/*
	 * we're checking the number of arguments and if there are wrong arguments just show the usage info and exit
	 */	

	if(argc == 1) {
		usage();	
		return 0;
	}

	/*
	 * otherwise go ahead
	 */

	else {
		 printw("SYN: %i\n", tcph->syn);
		 printw("FIN: %i\n", tcph->fin);
		//usage();
		//return 0;
	}

	tcp();

	endwin();     
	return 0;
}
 
