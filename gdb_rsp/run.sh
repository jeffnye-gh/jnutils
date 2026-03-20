(echo "client/client.cpp"; cat client/client.cpp; \
 echo "client/client.h"; cat client/client.h; \
 echo "client/cmain.cpp"; cat client/cmain.cpp; \
 echo "common/common.h"; cat common/common.h; \
 echo "server/client_interface.cpp"; cat server/client_interface.cpp; \
 echo "server/cmdinterp.h"; cat server/cmdinterp.h; \
 echo "server/commands.cpp"; cat server/commands.cpp; \
 echo "server/registration.cpp"; cat server/registration.cpp; \
 echo "server/server.cpp"; cat server/server.cpp; \
 echo "server/server.h"; cat server/server.h; \
 echo "server/smain.cpp"; cat server/smain.cpp; \
) > outputfile
