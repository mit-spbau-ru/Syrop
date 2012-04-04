import os

# creates the configuration file if necessary
# and calls the substitution of new settings
def setupSettings (settings):
	if settings.hasProxy("http"):
		lst = splitProxy(settings.getProxy("http"))
		makeConfigFile()
		copyBackupFile(lst[0], lst[1])

def cleanupSettings ():
	name = os.path.expanduser("~/.ssh/config")
	if os.path.exists(name + ".old"):
		os.rename(name + ".old", name)

# creates file if it does not exist
def makeConfigFile ():
	name = os.path.expanduser("~/.ssh/config")
	if not os.path.exists(name):
		cfg = open(name, "w")
		cfg.close()

def splitProxy (proxy):
	return proxy.split(':')

# creates a backup file 
# and copies the old configuration in it
# while copying it into the new one
# with changed proxy settings
def copyBackupFile (server, port):
	name = os.path.expanduser("~/.ssh/config")
	os.rename( name, name + ".old" )
	config = open( name + ".old", "r" )
	outconf = open( name, "w" )
	setProxy = False
	for line in config.readlines():
		newline = line.strip();
		if ( newline == "" ) :
			continue;
		parsed = newline.split();
		if parsed[0] == "ProxyCommand" :
			outconf.write ("ProxyCommand " + server + " " + port + " %h %p\n");
			setProxy = True
		else :
			outconf.write(newline + "\n")

	if not setProxy :
		outconf.write( "Host * \nProxyCommand " + server + " " + port + " %h %p\n")
	
	outconf.close()
	config.close()
