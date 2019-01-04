
index: 
	gcc -m32 -Wall -pedantic -g -o Program/out/bin/indexdb Program/C_STD_IQ/dataStr/index-db.c Program/C_STD_IQ/dataStr/util.c

query: 
	gcc -m32 -Wall -pedantic -g -o Program/out/bin/querydb Program/C_STD_IQ/dataStr/query-with-doclen.c Program/C_STD_IQ/dataStr/query-tools.c Program/C_STD_IQ/dataStr/util.c -lm

hash:
	gcc -m32 -Wall -pedantic -g -o Program/out/bin/querydb-hash Program/C_STD_IQ/dataStr/query-with-hash.c Program/C_STD_IQ/dataStr/query-tools.c Program/C_STD_IQ/dataStr/util.c -lm

server:
	gcc -m32 -Wall -std=gnu99 -o Program/C_STD_IQ/service/out/server Program/C_STD_IQ/service/server.c -lm

client:
	gcc -m32 -Wall -std=gnu99 -o Program/C_STD_IQ/service/out/client Program/C_STD_IQ/service/client.c -lm