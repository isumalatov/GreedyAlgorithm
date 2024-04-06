#Ilyas Umalatov X7278165E
all: mcp_greedy

mcp_greedy: mcp_greedy.cc
	g++ -o mcp_greedy mcp_greedy.cc

tar:
	tar -cvzf X7278165E.tar.gz mcp_greedy.cc makefile

clean:
	rm -f mcp_greedy X7278165E.tar.gz

