#ifndef _MSC_H_
#define _MSC_H_

// here write your header
#define FILE_SIZE(_size) \
    (uint8_t)((_size) & 0xff), \
    (uint8_t)(((_size) & 0xff00) >> 8), \
    (uint8_t)(((_size) & 0xff0000) >> 16), \
    (uint8_t)(((_size) & 0xff000000) >> 24)

#define AUTOMATA_CONTENT \
"Mačka\r\n"
#define README_CONTENT \
"# Rubber Ducky\r\n" \
"This is a read-only readme file. If you can access this file that means that it works!\r\n"

// Sense key table: https://www.seagate.com/files/staticfiles/support/docs/manual/Interface%20manuals/100293068j.pdf#G4.1602528
// Additional sense key table: https://www.seagate.com/files/staticfiles/support/docs/manual/Interface%20manuals/100293068j.pdf#G4.1602906
#endif // _MSC_H_
