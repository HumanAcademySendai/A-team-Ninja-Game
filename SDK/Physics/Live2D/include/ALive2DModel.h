/**
 *  ALive2DModel.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_ALIVE_2D_MODE_H__
#define __LIVE2D_ALIVE_2D_MODE_H__


#include "type/LDVector.h"
#include "Live2D.h"
#include "memory/LDObject.h"
#include "ModelContext.h"
#include "id/ParamID.h"
#include "id/DrawDataID.h"
#include "id/PartsDataID.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	class ModelImpl ;
	class DrawParam ;
	
	
	class ALive2DModel : public LDObject
	{
	public:
		static const int FILE_LOAD_EOF_ERROR = 1 ;			// ã??ã¿ã®æ«å°¾ãèª­ã¿è¾¼ããªã??åã?ã¨ã©ã¼
		static const int FILE_LOAD_VERSION_ERROR = 2 ;		// ã­ã¼ãã§ããªã?ã¼ã¸ã§ã³ã®ãã¡ã¤ã«
		
		static int INSTANCE_COUNT ;	
	
	
	public:	
		ALive2DModel() ;
		virtual ~ALive2DModel() ;
	
		
	
		// ãã©ã¡ã¼ã¿ã®å¤ãåå¾ãã?
		float getParamFloat( const char * paramID ) ;
		
		// ãã©ã¡ã¼ã¿ã®å¤ãè¨­å®ãã?
		void setParamFloat( const char * paramID , float value , float weight = 1.0f ) ;
		
		// ç¾å¨ã®å¤ã«å¯¾ãã¦ã??ã¿ãã¤ãã¦å¤ãå ããã?weight=1ã®ã¨ãã?æ?®ããå?ããã®ã¾ã¾å?ãã?
		void addToParamFloat( const char * paramID , float value , float weight = 1.0f ) ;
	
		// ç¾å¨ã®å¤ã«å¯¾ãã¦ã??ã¿ãã¤ãã¦å¤ãæãåãããã?weight=1ã®ã¨ãã?æ?®ããå?ããã®ã¾ã¾æãåãããã?
		void multParamFloat( const char * paramID , float mult , float weight = 1.0f  ) ;
		
		
		inline int getParamIndex( const char * paramID )
		{
			return modelContext->getParamIndex(ParamID::getID(paramID)) ;
		}
	
		
		inline int getParamIndex( ParamID* paramID )
		{
			return modelContext->getParamIndex( paramID ) ;
		}	

		inline float getParamFloat( int paramIndex )
		{
			return modelContext->getParamFloat( paramIndex ) ;
		}
	
		inline void setParamFloat( int paramIndex , float value , float weight = 1.0f)
		{
			if(weight==1)modelContext->setParamFloat( paramIndex , value ) ;
			else modelContext->setParamFloat( paramIndex ,  modelContext->getParamFloat( paramIndex )*(1-weight) + value*weight ) ;
		}
	
		inline void addToParamFloat( int paramIndex, float value , float weight = 1.0f)
		{
			modelContext->setParamFloat( paramIndex , modelContext->getParamFloat( paramIndex ) + value*weight ) ;
		}
	
		inline void multParamFloat( int paramIndex , float mult , float weight = 1.0f)
		{
			modelContext->setParamFloat( paramIndex , modelContext->getParamFloat( paramIndex )*(1.0f + (mult - 1.0f)*weight ) ) ;
		}
	
		// ååsaveParamããã¨ãã?ãã©ã¡ã¼ã¿å¤ãå¾©å?ãï¼?aveParamããã¦ã?ªããã°ä½ãããªã?¼?
		void loadParam() ;

		// ç¾å¨ã®ãã©ã¡ã¼ã¿å¤ãä¸?ç?«è¨æ?ãããloadParam()ã§å¾©å?§ããã?
		void saveParam() ;
	
		// ã??ã¿æ§é?ã®å¤æ´ããã¼ã?·®ãæ¿ããªã©ãè¡ã£ãå?åã«å¼ã¶
		virtual void init() ;
	
		// ãã©ã¡ã¼ã¿å¤æ´ãªã©ãè¡ã£ãå?åã«å¼ã¶
		virtual void update() ;

		// æç»å½ä»¤?ã?ã©ã?ãã©ã¼ã?ã¨ã«ãªã¼ãã?ã©ã¤ãããã??
		virtual void draw()  ;
		
		// ãã?ã??ä¸é?æåº¦ãè¨­å®?
		void setPartsOpacity( const char *partsID , float opacity ) ;
		void setPartsOpacity( int partsIndex , float opacity ) ;

		// ãã?ã??ä¸é?æåº¦ãåå¾?
		float getPartsOpacity( const char *partsID ) ;
		float getPartsOpacity( int partsIndex ) ;
		
		// ãã?ã??è¡¨ç¤ºã°ã«ã¼ããå¶å¾¡?éæ¨å¥¨??
		void setupPartsOpacityGroup_alphaImpl( const char* paramGroup[] , float deltaTimeSec ) ;
	
		// ã¢ã?«ã®ã??ã¿æ§é?ãè¨­å®?
		void setModelImpl(ModelImpl* m) ;

		// ã¢ã?«ã®ã??ã¿æ§é?ãåå¾?
		ModelImpl* getModelImpl() ;
	
		
		ModelContext * getModelContext(){ return modelContext ; }

		
		int getErrorFlags(){ return Live2D::getError() ; }
		
		// æ°ããå©ç¨ã§ããLive2Då?¨ã§ç®¡ç?ããã?¯ã¹ãã£çªå·ãç¢ºä¿?Avatarç¨)
		virtual int generateModelTextureNo() ;
		
		// Live2Då?¨ã§ç®¡ç?ããã?¯ã¹ãã£çªå·ãè§£æ¾(Avatarç¨)
		virtual void releaseModelTextureNo(int no) ;
	
		// ã­ã£ã³ãã¹ã®å¹?åå¾?
		float getCanvasWidth() ;

		// ã­ã£ã³ãã¹ã®é«ããåå¾?
		float getCanvasHeight() ;
	
		
		virtual DrawParam* getDrawParam(){ return NULL ; }
	
		
		virtual int getDrawDataIndex( const char * drawDataID )
		{
			return modelContext->getDrawDataIndex( DrawDataID::getID(drawDataID)) ;
		}
	
		
		virtual IDrawData* getDrawData( int drawIndex )
		{
			return modelContext->getDrawData( drawIndex ) ;
		}
		
		// æç»ç¨ã®ç¹åãè¿ãã?
		virtual l2d_pointf* getTransformedPoints( int drawIndex , int*pointCount) ;
		virtual l2d_index* getIndexArray( int drawIndex , int*polygonCount) ;
	
		// ãéæ¨å¥¨ãZBufferãè¨­å®ãã?
		// éå¸¸ãæç»ã«ã¯å¿?¦ãªã??ã§Zå¤ã¯è¨­å®ãããªã?ããã§ã¼ãã¤ã³ãã¢ã¦ããªã©ã®éæ?åº¦ãæç»ããå ´åã«å¿?¦ã?
		void updateZBuffer_TestImpl( float startZ , float stepZ )
		{
			modelContext->updateZBuffer_TestImpl( startZ , stepZ ) ;
		}
	
		
		inline int getPartsDataIndex( const char * partsID )
		{
			return modelContext->getPartsDataIndex(PartsDataID::getID(partsID)) ;
		}
		
		
		inline int getPartsDataIndex( PartsDataID* partsID )
		{
			return modelContext->getPartsDataIndex( partsID ) ;
		}

		
		void setPremultipliedAlpha(bool b);
		bool isPremultipliedAlpha();
		
		void setAnisotropy(int n);
		int getAnisotropy();


	#if L2D_ALPHA_IMPL_LAYOUT
		// ãä»®å®è£??ã¢ã?«ã®éç½®æ??ãè¿ã
		// ãã¤ã³ã¿ãç´æ¥è¿ã.å?®¹ãæ´æ°ããã¨ç´æ¥åæ ããã?
		//{ x , y , anchorX , anchorY , scaleX , scaleY }
		float* getLayout_alphaImpl(){ return layout_alphaImpl ; }
	#endif
		
	#ifdef L2D_DEBUG
		void dump() ;
	#endif
	
	protected:
		//------------ static method ------------
		// 2013/04/02 beta2 ã¨ã©ã¼ãã©ã°ãè¿ãããã«ä¿®æ­£
		static l2d_uint32 loadModel_exe( ALive2DModel *ret , const LDString & filepath ) ;
		static l2d_uint32 loadModel_exe( ALive2DModel *ret , const void * buf , int bufSize ) ;
	
	private:
		//Prevention of copy Constructor
		ALive2DModel( const ALive2DModel & ) ;				
		ALive2DModel& operator=( const ALive2DModel & ) ;
	
		
	protected:
		//------------ field ------------
		ModelImpl*			modelImpl ;						// ã¢ã?«ã®ã??ã¿æ§é?
		ModelContext*		modelContext ;					// ã¢ã?«ã®ç¶æ?		
//		int					errorFlags ;					// ã¨ã©ã¼ãã©ã°(1.00beta2ããç ´æ£?Live2D::setError()ã«çµ±å?
	
	#if L2D_ALPHA_IMPL_LAYOUT
		float layout_alphaImpl[6] ;//{ x , y , anchorX , anchorY , scaleX , scaleY }
	#endif
		
	};

} 
//------------ LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_ALIVE_2D_MODE_H__
