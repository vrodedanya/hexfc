install:
	gcc hex.c -o hexfc
	sudo chmod +x hexfc 
	sudo mv hexfc /usr/local/bin 
