# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.ext_recast.Debug:
/Users/jangdongmin/Desktop/photobox/ios-build/lib/Debug/libext_recast.a:
	/bin/rm -f /Users/jangdongmin/Desktop/photobox/ios-build/lib/Debug/libext_recast.a


PostBuild.ext_recast.Release:
/Users/jangdongmin/Desktop/photobox/ios-build/lib/Release/libext_recast.a:
	/bin/rm -f /Users/jangdongmin/Desktop/photobox/ios-build/lib/Release/libext_recast.a


PostBuild.ext_recast.MinSizeRel:
/Users/jangdongmin/Desktop/photobox/ios-build/lib/MinSizeRel/libext_recast.a:
	/bin/rm -f /Users/jangdongmin/Desktop/photobox/ios-build/lib/MinSizeRel/libext_recast.a


PostBuild.ext_recast.RelWithDebInfo:
/Users/jangdongmin/Desktop/photobox/ios-build/lib/RelWithDebInfo/libext_recast.a:
	/bin/rm -f /Users/jangdongmin/Desktop/photobox/ios-build/lib/RelWithDebInfo/libext_recast.a




# For each target create a dummy ruleso the target does not have to exist
