import os

# creates the configuration file if necessary
# and calls the substitution of new settings
def setupSettings (settings):
	if settings.hasProxy("http"):
		lst = splitProxy(settings.getProxy("http"))
		makeConfigFile()
		copyBackupFile(lst[0], lst[1])

# removes the last settings 
# clears comments before the previous settings if there are any
def cleanupSettings ():
	name = os.path.expanduser("~/.ssh/config")
	if os.path.exists(name) :

		os.rename( name, name + ".old" )
		config = open( name + ".old", "r" )
		outconf = open( name, "w" )
		firstUndo = True
	
		for line in config.readlines():
			newline = line.strip();
			if ( newline == "" ) :
				continue;
			parsed = newline.split();
			if parsed[0] == "#ProxyCommand" and firstUndo:
				#outconf.write('#syrop begin\n')
				outconf.write (newline [1:len(newline) ] + "\n")
				firstUndo = False
				#outconf.write('#syrop end\n')
			elif parsed[0] == "ProxyCommand" :
				continue
			else:
				outconf.write(newline + "\n")


		outconf.close()
		config.close()
		os.remove ( name + ".old" )
	

# creates file if it does not exist
def makeConfigFile ():
	name = os.path.expanduser("~/.ssh/config")
	if not os.path.exists(name):
		cfg = open(name, "w")
		cfg.close()

def splitProxy (proxy):
	return proxy.split(':')

 
# hides an old configuration with comments
# and addss new settings
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
			#outconf.write('#syrop begin\n')
			outconf.write ("ProxyCommand " + server + " " + port + " %h %p\n")
			#outconf.write('#syrop end\n')

			outconf.write ("#" + newline + "\n")
			setProxy = True
		else :
			outconf.write(newline + "\n")

	if not setProxy :
		#outconf.write('#syrop begin\n')
		outconf.write( "Host * \nProxyCommand " + server + " " + port + " %h %p\n")
		#outconf.write('#syrop end\n')

	outconf.close()
	config.close()
	os.remove ( name + ".old" )
