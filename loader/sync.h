#ifndef __SYNC_H__
#define __SYNC_H__

#include "common.h"

typedef enum {
  TRACK_RAMP    = 1, /* set constant value */
  TRACK_LINEAR  = 2, /* lerp to the next value */
  TRACK_SMOOTH  = 3, /* smooth curve to the next value */
  TRACK_TRIGGER = 4, /* count down (with every frame) from given number */
  TRACK_EVENT   = 5  /* like ramp but value is delivered only once */
} __attribute__((packed)) TrackTypeT;

#define END_KEY  -1
#define CTRL_KEY -2

typedef struct {
  short frame;
  short value;
} TrackKeyT;

/*
 * A few simplifying assumptions:
 * (1) There's at least one data key in the track.
 * (2) Default track's type is TYPE_LINEAR.
 * (3) There's always a data key before the end key.
 * (4) There's at most single control key before data key.
 */

typedef struct Track {
  /* private */
  TrackKeyT *curr;
  TrackKeyT *next;
  TrackTypeT type;
  short interval;
  short delta;
  bool pending;
  /* public: provided by user */
  const char *name;
  TrackKeyT data[0];
} TrackT;

extern TrackT *__TRACK_LIST__[];

void InitTracks(void);

__regargs void TrackReset(TrackT *track);
__regargs TrackT *TrackLookup(const char *name);
__regargs short TrackValueGet(TrackT *track, short frame);

#endif
