/**
 *  DDTexture.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_DDTEXTURE_H__
#define __LIVE2D_DDTEXTURE_H__


#ifndef __SKIP_DOC__

#include "../Live2D.h"
#include "IDrawData.h"
#include "../param/PivotManager.h"
#include "IDrawContext.h"

#ifdef L2D_TARGET_D3D
# include <d3dx9.h>
# include "../graphics/DrawParam_D3D.h"
#endif

#ifdef L2D_TARGET_PS4
#include <gnmx.h>
#endif

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 
	class DDTextureContext ;
	
	
	
	class DDTexture : public IDrawData
	{
	public:
		static const int OPTION_FLAG_BARCODE_KANOJO_COLOR_CONVERT = 0x1 ;// ãã?ã³ã¼ãã«ãã¸ã§ã§è²å¤ãè¡ãè¦ç´??å ´å?
		
		static const int MASK_COLOR_COMPOSITION = 0x1E ;//011110 
	
		static const int COLOR_COMPOSITION_NORMAL  = 0 ;// éå¸¸
		static const int COLOR_COMPOSITION_SCREEN  = 1 ;// ã¹ã¯ãªã¼ã³
		static const int COLOR_COMPOSITION_MULTIPLY= 2 ;// ä¹ç®?
	
		static int INSTANCE_COUNT ;
	
	public:
		DDTexture() ;
		virtual ~DDTexture(void) ;
		
	public:
		virtual void readV2(BReader & br , MemoryParam* memParam ) ;

		void initDirect(MemoryParam* memParam) ;
	
		//  æ?®ãããã¯ã¹ãã£çªå·ã«ã»ã?
		void setTextureNo(int no){ this->textureNo = no ; }
	
		//  ã?¯ã¹ãã£çªå·åå¾?
		int getTextureNo(){ return this->textureNo ; }
		
		//  uvéå? [ numPts*2 ]
		l2d_uvmapf * getUvMap(){ return this->uvmap ; }
		
		//  ç¹æ°ãè¿ã
		int getNumPoints(){ return this->numPts ; }
	
		//  ããªã´ã³æ°ãè¿ã
		int getNumPolygons(){ return this->numPolygons ; }
		
		virtual IDrawContext* init(ModelContext &mdc) ;
		
		virtual void setupInterpolate(ModelContext &mdc , IDrawContext* cdata ) ;
		
		virtual void setupTransform(ModelContext &mdc , IDrawContext* cdata ) ;
	
		virtual void draw( DrawParam & dp , ModelContext &mdc , IDrawContext* cdata ) ;
	
	#ifdef L2D_TARGET_D3D
	
		void setupBufD3D( DrawParam_D3D& dpD3D , ModelContext &mdc , DDTextureContext* cdata ) ;
	
		virtual void deviceLost( IDrawContext* drawContext ) ;
	#endif
		
		//  ã?¯ã¹ãã£ã¿ã¤ãåå¾?
		virtual int getType(){ return TYPE_DD_TEXTURE ; }// 
	
		int getOptionFlag(){ return this->optionFlag ; }
	
		virtual void setZ_TestImpl( ModelContext &mdc , IDrawContext* _cdata , float z ) ;
	
		l2d_index*  getIndexArray(int* polygonCount);

	#if AVATAR_OPTION_A
		//  è²åå¾?
		int getOption_KanojoColor(){ return this->optionKanojoColor ; }
	
	#endif
	
	#ifdef L2D_DEBUG
		virtual void dump() ;
	#endif
	
	private:
		// Prevention of copy Constructor
		DDTexture( const DDTexture & ) ;				
		DDTexture& operator=( const DDTexture & ) ;		
	
	private:
		int						textureNo ;				// ä½¿ç¨ããã?¯ã¹ãã£çªå·?ã¢ã?«ã®ç®¡ç?ããã¯ã¹ãã£çªå·??
		int						numPts ;				// é ç¹ã®æ°??SPã®sceGumDrawArray ã§ã¯ 65535ã¾ã§ã«ãªãï¼?
		int						numPolygons ;			// ããªã´ã³ã®æ°
		int						optionFlag ;			// ãªãã·ã§ã³è¨­å®?
		
		// --- å¿?¦ã«å¿ãã¦è¨­å®ããããªãã·ã§ã³å¤
	#if AVATAR_OPTION_A
		int						optionKanojoColor ;		// Avatarã®ãªãã·ã§ã³??ptionFlag & DDMorph.OPTION_FLAG_BARCODE_KANOJO_COLOR_CONVERTãç«ã£ã¦ã?å ´åï¼?
	#endif
		
		l2d_index *				indexArray ;			// é ç¹ã¤ã³ã?ã¯ã¹éå? [numPolygons*3]
	
		//  points ( Pivotéå? )ã®ã«ã¼ã« ( ä¾? xnum=3 , ynum=4 , znum=2 ã®ãã©ã¡ã¼ã¿ã®å ´å?)
		//  [x0,y0,z0],[x1,y0,z0],[x2,y0,z0]  , [x0,y1,z0],[x1,y1,z0],[x2,y1,z0].. ã¨ãªã?
		
		LDVector<l2d_paramf*>*	pivotPoints ;			// è£éç¨ã®pivotãå?ã¦æã¤é ç¹éå? [numPivots][numPts*2]
		l2d_uvmapf *			uvmap ;					// uvéå? [ numPts*2 ]
		int						colorCompositionType ;	// è²åæ?ã®ã¿ã¤ã?
		bool					culling ;				// 1.0beta3
	};
	
	
	class DDTextureContext : public IDrawContext 
	{
	public:
		DDTextureContext(IDrawData* src) ;
		virtual ~DDTextureContext() ;
		
	public:		
		// å¤ææ¸ã¿ã®ç¹åãè¿ã 
		// pointCount ã¯ç¹ã®æ°ãè¿ã?ç¹??,y?ãpointCountåä¸¦ã¶ã®ã§ãpointCount*2ã®éå?ã¨ãªãï¼?
		l2d_pointf* getTransformedPoints( int* pointCount ) ;
	
	public:		
		int 				tmpBaseDataIndex ;		// IBaseDataã®ã¤ã³ã?ã¯ã¹ãä¸å¤ãªã®ã§ä¸?º¦åå¾ããã?ãã
		l2d_pointf * 		interpolatedPoints ;	// è£éãããç¹å?	PSPã®å ´åã?ã[numPts*5]ã? OpenGLã®å ´åã? [numPts*2]( texture x,y , è£éã»å¤å½¢ãããå¾ã?ç¹ x,y , z=0 ) 
		l2d_pointf * 		transformedPoints ;		// å¤å½¢ãããç¹å?
		l2d_pointf * 		drawPoints ;			// æç»ç¨ã®ç¹åï¼ããã«ãããã¡ç¨ã®å ´åã?ã¹ã¯ã??ãã¦ä½¿ãããï¼?.9.00b14
		
		unsigned char 		not_updated_count ;		// æ´æ°ãããªãã£ãåæ°ãã«ã¦ã³ããã\n?åç®ã¨?åç®ã§æå³ãæã¤ã?ndouble bufferã®ã¨ãäºåæ´æ°ãããªããã°ãã?ã¾ã¾åã?å¤ãä½¿ãã
		
	#ifdef L2D_TARGET_D3D
		LPDIRECT3DVERTEXBUFFER9 		pUvBuf ; // Uvéå?
		LPDIRECT3DINDEXBUFFER9 			pIndexBuf ; // ã¤ã³ã?ã¯ã¹éå?
	#endif

	#ifdef L2D_TARGET_PS4
		bool initializedBuffer;
		float* color;//éæ?åº¦å«ããæãåãããè²ãfloat[4]ãã·ã§ã¼ã?¨
		sce::Gnm::Buffer buffers[2];//position , textureUV 
	#endif
	} ;
} 
//------------ LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

#endif	// __LIVE2D_DDTEXTURE_H__

