#!/usr/bin/env python
# -*- coding: utf-8 -*-
import ConfigParser, os, re
from subprocess import call
from subprocess import Popen
from subprocess import PIPE

def backupSettings () :
  
    for t in ( "http", "https", "ftp","socks" ) :
	    
        # save the previous settings if proxy is used or not
        olduse = Popen ( ["gconftool", "-g", "/system/" + t + "_proxy/use_" + t + "_proxy"], 
                        stdout=PIPE ).communicate()[0]
        ret = call ( "gconftool -s /system/" + t + "proxy/old_use_" + t + "_proxy -t bool " + str(olduse), 
                        shell = True )                 
              
        if olduse :
                # save the old host name
                oldhost = Popen ( ["gconftool", "-g", "/system/" + t + "_proxy/host"], 
                                stdout=PIPE ).communicate()[0] 
                ret = call ( "gconftool -s /system/" + t + "_proxy/old_host -t int " + oldhost, 
                                    shell = True ) 
 
                # save the old port number
                oldport = Popen ( ["gconftool", "-g", "/system/" + t + "_proxy/port"], 
                                stdout=PIPE ).communicate()[0] 
                ret = call ( "gconftool -s /system/" + t + "_proxy/old_port -t int " + oldport, 
                                    shell = True )  
                 
                # save the old user name
                olduser = Popen ( ["gconftool", "-g", "/system/" + t + "_proxy/authentification_user"], 
                                stdout=PIPE ).communicate()[0] 
                ret = call ( "gconftool -s /system/" + t + "_proxy/old_user -t string " + olduser, 
                                    shell = True ) 
                
                # save the old password
                oldpwd = Popen ( ["gconftool", "-g", "/system/" + t + "_proxy/authentification_password"], 
                                stdout=PIPE ).communicate()[0] 
                ret = call ( "gconftool -s /system/" + t + "_proxy/old_pwd -t string " + oldpwd, 
                                    shell = True )   
###
### @param settings - dictionary of settings
### @param s - type of protocol
###
def setupSettings ( settings ) :     

    all_attrs = {}
    if "user_pass" in settings :
        res = settings["user_pass"].split(":")
        all_attrs["user"] = res[0]
        all_attrs["password"] = res[1]

    
	# iterate over protocols in settings 
    for t in ( "http", "https", "ftp","socks" ) :

        if t in settings :
            # obtain settings
            params = splitProxyString(settings[t])
            if "host" in params and "port" in params :
                all_attrs["host"] = params["host"]
                all_attrs["port"] = params["port"]
            
                # set use of proxy
                ret = call ( "gconftool -s /system/" + t + "_proxy/use_" + t + "_proxy -t bool true ", 
                                shell = True )                  

                # specify the new host name
                ret = call ( "gconftool -s /system/" + t + "_proxy/host -t string " + all_attrs["host"], shell = True ) 

                # set the new port number
                ret = call( "gconftool -s /system/" + t + "_proxy/port -t int " + all_attrs["port"], shell = True ) 
        
                if "user" in all_attrs:
                    # set the new user name
                    ret = call( "gconftool -s /system/" + t + "_proxy/authentification_user -t string " + all_attrs["user"], shell = True )
        
                if 'password' in all_attrs:
                    # set the new password
                    ret = call( "gconftool -s /system/" + t + "_proxy/authentification_password -t string " + all_attrs["password"], shell = True )
        else :
            ret = call ( "gconftool -s /system/" + t + "_proxy/use_" + t + "_proxy -t bool false ", shell = True )                  
             
def cleanupSettings ():

    # iterate over protocols
    for s in { 'http', 'ftp' } :
        olduse = Popen ( ["gconftool", "-g", "/system/" + s + "_proxy/old_use_" + s + "_proxy"], 
                        stdout=PIPE ).communicate()[0] 
        # if proxy was set in previous settings...
        if (olduse) :
        
            # ...reset the settings                                     
            call( "gconftool -s /system/" + s + "_proxy/use_" + s + "_proxy " + olduse, 
                            shell = True ) 
            
            oldhost = Popen ( ["gconftool", "-g", "/system/" + s + "_proxy/old_host"], 
                            stdout=PIPE ).communicate()[0] 
            ret = call ( "gconftool -s /system/" + s + "_proxy/host -t string " + str(oldhost), 
                                    shell = True )        

            oldport = Popen ( ["gconftool", "-g", "/system/" + s + "_proxy/old_port"], 
                                stdout=PIPE ).communicate()[0] 
            ret = call ( "gconftool -s /system/" + s + "_proxy/port -t int " + str(oldport), 
                                    shell = True ) 

        
            olduser = Popen ( ["gconftool", "-g", "/system/" + s + "_proxy/old_user"], 
                                stdout=PIPE ).communicate()[0] 
            ret = call ( "gconftool -s /system/" + s + "_proxy/authentification_user -t string " + str(olduser), 
                                    shell = True ) 

                
            oldpwd = Popen ( ["gconftool", "-g", "/system/" + s + "_proxy/old_pwd"], 
                            stdout=PIPE ).communicate()[0] 
            ret = call ( "gconftool -s /system/" + s + "_proxy/authentification_password -t string " + str(oldpwd), 
                                    shell = True ) 

  	      
#waits for string of type [user:password@]server[:port]
def splitProxyString (conf):
    params = {}
    m = re.match(r"^([^:@]+){1}[:]([^:@]+){1}$", conf.strip(None))
	
    if m is not None:
        if m.group(1) is not None:
            params["host"] = m.group(1)
        if m.group(2) is not None:
            params["port"] = m.group(2)
    print params
    return params

#
# usage example :
#
#conf = {'http' : "us:pas@12.12.12.12:1"}
#setupSettings(conf)
#cleanupSettings()
