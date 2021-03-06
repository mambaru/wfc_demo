//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/logger.hpp>

#define HASH_LOG_ERROR(X)    WFC_LOG_ERROR( "DEMO:HASH", X )
#define HASH_LOG_WARNING(X)  WFC_LOG_WARNING( "DEMO:HASH", X )
#define HASH_LOG_MESSAGE(X)  WFC_LOG_MESSAGE( "DEMO:HASH", X )
#define HASH_LOG_FATAL(X)    WFC_LOG_FATAL( "DEMO:HASH", X )
#define HASH_LOG_BEGIN(X)    WFC_LOG_BEGIN( "DEMO:HASH", X )
#define HASH_LOG_END(X)      WFC_LOG_END( "DEMO:HASH", X )
#define HASH_LOG_DEBUG(X)    WFC_LOG_DEBUG( "DEMO:HASH", X )
#define HASH_LOG_TRACE(X)    WFC_LOG_TRACE( "DEMO:HASH", X )
#define HASH_LOG_PROGRESS(X) WFC_LOG_PROGRESS( "DEMO", X )
