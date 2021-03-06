/**
 *  PartsDataID.h
 * 
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_PARTS_DATA_ID_H__
#define __LIVE2D_PARTS_DATA_ID_H__


#include "../Live2D.h"
#include "ID.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	
	class PartsDataID  : public ID
	{
	public:
		const static int L2D_PARTS_ID_INITIAL_CAPACITY = 64 ;
		
	public:
		// IDãåå¾ãã?
		// ã»åä¸??å¤ãæã¤å¨ã¦ã®IDãã?åããã¤ã³ã¿ãæããã¨ãä¿è¨¼ãã ?åä¸??ç¢ºèªãã?= æ¯è¼?ã§è¯ã?¼?\n
		// ã»Live2D::dispose()æã«è§£æ¾ããã?
		static PartsDataID * getID(const live2d::LDString &str ) ;

		static PartsDataID * getID(  const RefString& refStr ) ;
	
		// ãªãªã¼ã¹ç¨ã¡ã½ã???ive2D::diposeããå¼ã°ãã)
		static void releaseStored_notForClientCall() ;
	
	public:
		/****************************************************************************
		@~english

		@~japanese
		@brief		IDãCè¨?ªã?æ?­å?ã¨ãã¦åå¾?
		@return		IDæ?­å?
		****************************************************************************/
		const char * toChar(){ return id.c_str() ; }
	
	private:	
		// Constructor
		PartsDataID() ;									
		PartsDataID( const char* str ) ;					
		PartsDataID(const live2d::LDString &str );		

		//Prevention of copy Constructor	
		PartsDataID( const RefString& refStr ) ;		
		PartsDataID( const PartsDataID & ) ;			
		PartsDataID& operator=( const PartsDataID & ) ; 

		// Destructor
		virtual ~PartsDataID();
		
	private:	
		//------------ static ------------
		static LDVector<PartsDataID*>*		idlist ;
		
	private:	
		//------------ this ------------
		live2d::LDString 					id ;// çæ?æã«è¤?£½ããã¦ã?ãããDestructorã§éæ¾ãã
	};
}
//------------ LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_PARTS_DATA_ID_H__
