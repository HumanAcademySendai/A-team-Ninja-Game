/**
 *  BReader.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_B_READER_H__
#define __LIVE2D_B_READER_H__


#ifndef __SKIP_DOC__


#include "../memory/LDObject.h"
#include "ByteBuffer.h"

#include "../type/LDVector.h"

//--------- LIVE2D NAMESPACE ------------
namespace live2d
{
	class AMemoryHolder ;
	
	
	class BReader : public live2d::LDObject 
	{
	public:
		static const int FLAG_READ_AS_USHORT_ARRAY	= 0x1 ;// int[]ãã?ã­ã¼ãæã«ushort[]ã¨ãã¦æ±ã?
		static const int FLAG_MALLOC_ON_GPU			= 0x2 ;// GPUä¸ã«ã¡ã¢ãªãç¢ºä¿ãã?
	
	
		// ã­ã¼ãæã«ãªãã¸ã§ã¯ããä¿ç®¡ããã??ãã«ã®ãµã¤ãº
		// å°ãã?¨vectorã®resizeãçºçããã?å¤§ããã¨ã¡ã¢ãªãå§è¿«ãã
		// ä½¿ç¨ã¡ã¢ãªã¯ sizeof(void*) * LOAD_OBJECT_INITIAL_CAPACITYã¨ãªã?
		// ä»å¾ã?ãã¢ã?«ã®ä¸­ã«ãªãã¸ã§ã¯ãæ°ãåãè¾¼ã?¹å¼ã«å¤æ´ãã
		static const int LOAD_OBJECT_INITIAL_CAPACITY = 10000 ; 
	
	
	    // éæ¾ã®æ¹æ³ãç¢ºå®ããå®å?ã§ã¯ãªã?ãå¿?å¤é¨ã§éæ¾ããããã«å¤æ´
		//BReader( const char * buf , int length , bool deleteBufOnDestructor );
		BReader( const char * buf , int length );
		virtual ~BReader();
		
		//  ãã¡ã¤ã«ãã©ã¼ãããã?ãã?ã¸ã§ã³ 
		int getFormatVersion(){ return formatVersion ; }
	
		void setFormatVersion(int version){ formatVersion = version ; }
		
		void rollback( int byteLen ) ;// æ?®ã?ãã¤ãæ°æ»ã?
	
		// Flagsã«ã¯ä»¥ä¸ãæ¸¡ã?
		//	FLAG_READ_AS_USHORT_ARRAY	= 0x1 ;// int[]ãã?ã­ã¼ãæã«ushort[]ã¨ãã¦æ±ã?
		//	FLAG_MALLOC_ON_GPU			= 0x2 ;// GPUä¸ã«ã¡ã¢ãªãç¢ºä¿ãã?
		void * readObject( MemoryParam * memParam , int cno = -1 , int flags = 0 ) ;
		bool readBit() ;
		int readNum(){ return bin.readNum() ; } ;// å¯å¤é·ã®é·ããåå¾ãã?1..4ãã¤ãã¾ã§ãé·ãã«å¿ãã¦ä½¿ã??ãã
		float readFloat(){	checkBits() ; return bin.readFloat() ;	}
		double readDouble(){ checkBits() ; return bin.readDouble() ;	}
		long long readLong(){ checkBits() ; return bin.readLong() ;	}
		int readInt() { checkBits() ; return bin.readInt() ;}
		bool readBoolean(){ checkBits() ; return bin.readBoolean() ;}
		char readByte(){ checkBits() ; return bin.readByte() ;}// 1byteå?¿ã??avaã®ãã¤ãã¨å¯¾å¿ã?charã¯Javaã¨åãç°ãªãã?ã§åç§°ããåé¿??
		short readShort(){ checkBits() ; return bin.readShort() ;	}
	
		//  ?ã?ã¤ã³ã¿?ãè¿ãã?å¤é¨ã§L2D_FREE( )ãå¿?¦?
		double* readArrayDouble(MemoryParam* memParam,int *ret_length){ checkBits() ; return bin.readArrayDouble(memParam, ret_length) ;	}// size, float* ãæ»ãå¿?¦ããã
		float* readArrayFloat(MemoryParam* memParam,int *ret_length){ checkBits() ; return bin.readArrayFloat(memParam, ret_length) ;	}// size, float* ãæ»ãå¿?¦ããã
	
		int * readArrayInt(MemoryParam* memParam,int *ret_length){ checkBits() ; return bin.readArrayInt(memParam, ret_length ) ;}
		unsigned short * readArrayIntAsUShort(MemoryParam* memParam,int *ret_length){ checkBits() ; return bin.readArrayIntAsUShort(memParam, ret_length ) ;}
	
		LDVector<double>* readArrayDoubleAsVector(MemoryParam* memParam){ checkBits() ; return bin.readArrayDoubleAsVector(memParam) ;	}// size, float* ãæ»ãå¿?¦ããã
		LDVector<float>* readArrayFloatAsVector(MemoryParam* memParam){ checkBits() ; return bin.readArrayFloatAsVector(memParam) ;	}// size, float* ãæ»ãå¿?¦ããã
		LDVector<int> * readArrayIntAsVector(MemoryParam* memParam){ checkBits() ; return bin.readArrayIntAsVector(memParam) ;}
		
		//  ãã«ããã¤ãæå­ã?æªæ¤è¨¼??ytesã§é·ããæ?®ãã¦ã?ã®ã§ããã§ã®ã¨ã©ã¼ã¯ã§ãªã?¼?
		live2d::LDString* readString(MemoryParam* memParam ){ checkBits() ; return bin.readString(memParam) ;	}
		RefString& readStringAsRef(){ checkBits() ; return bin.readStringAsRef() ;	}
	
		// cã®ãã¤ã³ã¿ãè¿ããçµç«¯è¨å·ã¾ã§é²ãã
		const char* readCStr(){ checkBits() ; return bin.readCStr() ; }
		char* getCurPtr(){ return bin.getCurPtr() ; }
		void setEndian( bool isBigEndian ) { bin.setEndian(isBigEndian) ; }
		void skip( int bytes ){ bin.skip( bytes ) ; }

		// èª­ã¿è¾¼ã¿ãªããEndianãå?ãæ¿ãã¦ã?å ´åã«true
		// ä¸?º¦èª­ã¿è¾¼ãã ãããã¡ãå?åº¦ã­ã¼ãããå?åã«äºåç®ãåãEndianã§æ±ããããã«ãã
		void setChangeEndian( bool change ) { bin.setChangeEndian( change ) ; }
	
	#if L2D_SAMPLE
		static void TEST_1() ;
		static void TEST_MODEL_LOAD() ;
	#endif
	
		
	private:
		void* read_array_ent( MemoryParam* memParam ,int targetClassNo, int restDimension) ;// æ»ãå?ã¯ã??åå ( ããªããã£ããããã®ã§ãå¿?ããObject[]ã§ã¯ãªã?)
	
		void checkBits()
		{
			if( bitCount != 0 ) bitCount = 0 ;
		}
		
		int formatVersion ;
		
		ByteBuffer bin ;
		int bitCount ; //= 0 ;
		int bitBuff ;//= 0 ;// ç¾å¨ã®ããããã©ã°ãç®¡ç?
	
		// TODO ãªãã¸ã§ã¯ããªã¹ãã?ç®¡ç?å¼·å?
		LDVector<void*> loadObjects ;// çæ?ããããªãã¸ã§ã¯ãã?å¨ã¦ç»é²ãããã?ã­ã¼ãçµæãªã®ã§ä¸­èº«ã¯è§£æ¾ããªã?
		
	};
}
//------------------------- LIVE2D NAMESPACE -------------

#endif // __SKIP_DOC__

#endif		// __LIVE2D_B_READER_H__
