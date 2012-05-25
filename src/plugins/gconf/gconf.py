#!/usr/bin/env python
# -*- coding: utf-8 -*-
import ConfigParser, os, re
from subprocess import Popen
from subprocess import PIPE

def backupSettings ():
    for s in settings :
        t = s.strip()
	    # save the previous settings if proxy is used or not
        olduse = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/use_"+t+"_proxy"], stdout=PIPE ).communicate()[0]
        ret = subprocess.call ( "gconftool -s /system/"+t+"proxy/old_use_"+t+"_proxy -t bool " + str(olduse), shell = True )                 
              
            
        if olduse :
                # save the old host name
                oldhost = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/host"], stdout=PIPE ).communicate()[0] 
                ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/old_host -t int " + oldhost, shell = True ) 
 
                # save the old port number
                oldport = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/port"], stdout=PIPE ).communicate()[0] 
                ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/old_port -t int " + oldport, shell = True )  
                 
                # save the old user name
                olduser = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/authentification_user"], stdout=PIPE ).communicate()[0] 
                ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/old_user -t string " + olduser, shell = True ) 
                
                # save the old password
                oldpwd = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/authentification_password"], stdout=PIPE ).communicate()[0] 
                ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/old_pwd -t string " + oldpwd, shell = True )   
###
### @param settings - dictionary of settings
### @param s - type of protocol
###
def setupSettings ( settings ) :     
	# iterate over protocols in settings 
    for s in settings :

        t = s.strip()
        # obtain settings
        params = splitProxyString(settings[t])
        
        # set use of proxy
        ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/use_"+t+"_proxy -t bool true ", shell = True )                  
        # if server name is specified ...

        if 'server' in params :
            # specify the new host name
            ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/host -t int " + params['server'], shell = True ) 

        # if port number is specified
        if 'port' in params :
            # set the new port number
            ret = subprocess.call( "gconftool -s /system/"+t+"_proxy/port -t int " + params['port'], shell = True ) 
        
        if 'user' in params:
            # set the new user name
            ret = subprocess.call( "gconftool -s /system/"+t+"_proxy/authentification_user -t string " + params['user'], shell = True )
        
        if 'password' in params:
            # set the new password
            ret = subprocess.call( "gconftool -s /system/"+t+"_proxy/authentification_password -t string " + params['password'], shell = True )
  	

def cleanupSettings ():

    # iterate over protocols
    for s in { 'http', 'ftp' } :
        olduse = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_use_"+s+"_proxy"], stdout=PIPE ).communicate()[0] 
        # if proxy was set in previous settings...
        if (olduse) :
        
            # ...reset the settings
            subprocess.call( "gconftool -s /system/"+s+"_proxy/use_"+s+"_proxy " + olduse, shell = True ) 
            
            oldhost = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_host"], stdout=PIPE ).communicate()[0] 
            ret = subprocess.call ( "gconftool -s /system/"+s+"_proxy/host -t int " + str(oldhost), shell = True )        

            oldport = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_port"], stdout=PIPE ).communicate()[0] 
            ret = subprocess.call ( "gconftool -s /system/"+s+"_proxy/port -t int " + str(oldport), shell = True ) 

        
            olduser = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_user"], stdout=PIPE ).communicate()[0] 
            ret = subprocess.call ( "gconftool -s /system/"+s+"_proxy/authentification_user -t string " + str(olduser), shell = True ) 

                
            oldpwd = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_pwd"], stdout=PIPE ).communicate()[0] 
            ret = subprocess.call ( "gconftool -s /system/"+s+"_proxy/authentification_password -t string " + str(oldpwd), shell = True ) 

  	      
def sectionString (string):
	m = re.match(r"^\[\s*(.+)\s*\]$", string.strip(None))
	if m is not None:
		return m.group(1)
	return None

#waits for string of type [user:password@]server[:port]
def splitProxyString (conf):
	params = {}
	m = re.match(r"^(([^:@]+)[:]([^:@]+)[@]){,1}([^:@]+){1}[:]([^:@]+){,1}$", conf.strip(None))

	if m is not None:
		if m.group(2) is not None:
			params['user'] = m.group(2)
		if m.group(3) is not None:
			params['password'] = m.group(3)
		if m.group(4) is not None:
			params['server'] = m.group(4)
		if m.group(5) is not None:
			params['port'] = m.group(5)

	return params

#
# usage example :
#
#conf = {'http' : "us:pas@12.12.12.12:1"}
#setupSettings(conf)
#cleanupSettings()
