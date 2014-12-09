#ifndef LINDA_H
#define LINDA_H

typedef struct _linda* linda;

#define LINDA_ID "$id"
#define LINDA_OID "$oid"

extern linda linda_open(const char* path1, const char* path2);

extern int linda_out(linda l, const char* s);

// These all return a managed pointer to a read buffer.

extern int linda_rd(linda l, const char* s, const char** dst);
extern int linda_rdp(linda l, const char* s, const char** dst);
extern int linda_in(linda l, const char* s, const char** dst);
extern int linda_inp(linda l, const char* s, const char** dst);

// Call only if needed to take control of buffer.

extern void linda_free(linda l);

extern int linda_get_length(linda l);			// last read
extern const uuid* linda_get_oid(linda l);		// last read
extern const uuid* linda_last_oid(linda l);		// last write

extern int linda_close(linda l);

#endif
