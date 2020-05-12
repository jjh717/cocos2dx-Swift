# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.ext_convertUTF.Debug:
/Users/jangdongmin/Desktop/photobox/ios-build/lib/Debug/libext_convertUTF.a:
	/bin/rm -f /Users/jangdongmin/Desktop/photobox/ios-build/lib/Debug/libext_convertUTF.a


PostBuild.ext_convertUTF.Release:
/Users/jangdongmin/Desktop/photobox/ios-build/lib/Release/libext_convertUTF.a:
	/bin/rm -f /Users/jangdongmin/Desktop/photobox/ios-build/lib/Release/libext_convertUTF.a


PostBuild.ext_convertUTF.MinSizeRel:
/Users/jangdongmin/Desktop/photobox/ios-build/lib/MinSizeRel/libext_convertUTF.a:
	/bin/rm -f /Users/jangdongmin/Desktop/photobox/ios-build/lib/MinSizeRel/libext_convertUTF.a


PostBuild.ext_convertUTF.RelWithDebInfo:
/Users/jangdongmin/Desktop/photobox/ios-build/lib/RelWithDebInfo/libext_convertUTF.a:
	/bin/rm -f /Users/jangdongmin/Desktop/photobox/ios-build/lib/RelWithDebInfo/libext_convertUTF.a




# For each target create a dummy ruleso the target does not have to exist
