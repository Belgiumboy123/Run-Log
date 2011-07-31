import glob

filenum = 0
totallines = 0
emptyline = 0
commentline = 0
sourceline = 0
headernum = 0
sourcenum = 0

def process( line ):
	global emptyline
	global commentline
	global sourceline
	line = line.lstrip()
	if( len( line ) == 0 ):#line.isspace() 
		emptyline += 1
	else:
		if( line.startswith("/**") or line.startswith( "/*" ) or line.startswith( "*/" ) or line.startswith( "//") ):
			commentline += 1
		else:
			sourceline += 1
        

def count( file ):
	global filenum
	global totallines
	filenum += 1
	f = open( file )
	for line in f.readlines():
		process( line )
		totallines += 1    
	f.close()

def main():

	path = ""

	global headernum
	global sourcenum
	
	headers = glob.glob( "*.h" )
	for header in headers:
		headernum += 1
		count( header )
    
	sources = glob.glob( "*.cpp" )
	for source in sources:
		sourcenum += 1
		count( source )
    
	print "Header files: " + str(headernum)
	print "Source files: " + str(sourcenum)
	print "Total Lines:  " + str( totallines)
	print "Empty lines: "  + str( emptyline )
	print "Comments: "     + str (commentline)
	print "Code: "         + str( sourceline )
    
    
main()