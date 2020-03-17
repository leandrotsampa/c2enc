#ifndef __HICODEC__
#define __HICODEC__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Defines the stream type supported by the decoder. **/
typedef enum {
	CODEC_ID_MPEG2,
	CODEC_ID_MPEG4,
	CODEC_ID_AVS,
	CODEC_ID_H263,
	CODEC_ID_H264,
	CODEC_ID_REAL8,
	CODEC_ID_REAL9,
	CODEC_ID_VC1,
	CODEC_ID_VP6,
	CODEC_ID_VP6F,
	CODEC_ID_VP6A,
	CODEC_ID_MJPEG,
	CODEC_ID_SORENSON,
	CODEC_ID_DIVX3,
	CODEC_ID_RAW,
	CODEC_ID_JPEG,
	CODEC_ID_VP8,
	CODEC_ID_MSMPEG4V1,
	CODEC_ID_MSMPEG4V2,
	CODEC_ID_MSVIDEO1,
	CODEC_ID_WMV1,
	CODEC_ID_WMV2,
	CODEC_ID_RV10,
	CODEC_ID_RV20,
	CODEC_ID_SVQ1,
	CODEC_ID_SVQ3,
	CODEC_ID_H261,
	CODEC_ID_VP3,
	CODEC_ID_VP5,
	CODEC_ID_CINEPAK,
	CODEC_ID_INDEO2,
	CODEC_ID_INDEO3,
	CODEC_ID_INDEO4,
	CODEC_ID_INDEO5,
	CODEC_ID_MJPEGB,
	CODEC_ID_MVC,
	CODEC_ID_HEVC,
	CODEC_ID_DV,
	CODEC_ID_VP9,
	CODEC_ID_NONE
} CODEC_ID;

typedef enum {
	FRAME_TYPE_NONE,
	FRAME_TYPE_AUTO,
	FRAME_TYPE_IDR,
	FRAME_TYPE_I,
	FRAME_TYPE_P,
} FRAME_TYPE;

/**
 * Defines the type of the event callback function.
 * Will be called when new frames is received, without call decoder_output function.
 */
typedef void (*HICODEC_FRAME_EVENT)(int32_t width, int32_t height, uint8_t *buffer, int32_t size, int64_t pts);

typedef struct {
	uint32_t hPlayer;
	uint32_t hWindow;
	CODEC_ID hCodec;
	uint32_t hPriv[128]; // Encoder use for private configs.
} SHICODEC;

/**
 * Get Version Info
 *
 *@return: Version Info
 */
const char *vl_get_version();

/**
 * Initialize the Encoder
 *
 *@param : codec_id
 *@param : width
 *@param : height
 *@param : frame_rate
 *@param : bit_rate
 *@param : gop GOP: I-frame maximum interval
 *@return: Return true on success and false on failure.
 */
bool vl_video_encoder_init(SHICODEC *codec, CODEC_ID codec_id, int width, int height, int frame_rate, int bit_rate, int gop);

/**
 * Video Encoding
 *
 *@param : *codec
 *@param : type
 *@param : in
 *@param : in_size
 *@param : out - H.264 need to include (0x00£¬0x00£¬0x00£¬0x01) Start code, internally allocated space (that is, the method allocates space when implemented) and must be in I420 format.
 *@return: Successfully returns the length of the encoded data. Failure returns <= 0
 */
int vl_video_encoder_encode(SHICODEC *codec, FRAME_TYPE type, uint8_t *in, int in_size, uint8_t **out);

/**
 * Destroy the Encoder
 *
 *@param : *codec
 */
void vl_video_encoder_destroy(SHICODEC *codec);

/**
 * Initialize the Decoder
 *
 *@param : codec_id
 *@param : *codec
 *@return: Return true on success and false on failure.
 */
bool vl_video_decoder_init(CODEC_ID codec_id, SHICODEC *codec);

/**
 * Video Decoding
 *
 *@param : handle
 *@param : in
 *@param : in_size
 *@param : out
 *@return: Successfully returns the length of the decoded data. Failure returns <= 0
 */
int vl_video_decoder_decode(SHICODEC *codec, uint8_t *in, int size, uint8_t **out);

/**
 * Input Video Buffer for Decoding
 *
 *@param : *codec
 *@param : in
 *@param : size
 *@param : pts
 *@return: Successfully returns true and false on failure
 */
bool vl_video_decoder_input(SHICODEC *codec, uint8_t *in, int size, int64_t pts);

/**
 * Output Video Buffer Decoded
 *
 *@param : *codec
 *@param : out
 *@param : pts
 *@return: Successfully returns the length of the decoded data. Failure returns < 0
 */
int vl_video_decoder_output(SHICODEC *codec, uint8_t **out, int64_t *pts);

/**
 * Callback for Output Video Buffer Decoded
 *
 *@param : *codec
 *@param : callback
 *@return: Successfully returns true and false on failure
 */
bool vl_video_decoder_register_event(SHICODEC *codec, HICODEC_FRAME_EVENT callback);

/**
 * Destroy the Decoder
 *@param : *codec
 */
void vl_video_decoder_destroy(SHICODEC *codec);

#ifdef __cplusplus
}
#endif

#endif /* __HICODEC__ */
