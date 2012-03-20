def setupSettings (settings):
	if settings.hasProxy("https"):
		print settings.getProxy("https")
	else:
		print settings.getProxy("http")

def cleanupSettings ():
	print "cleanned"