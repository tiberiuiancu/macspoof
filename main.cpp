#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/ethtool.h>
#include <linux/sockios.h>  // SIOCETHTOOL
#include <net/if.h>         // ifreq


typedef unsigned char BYTE;

typedef struct {
    int socket;
    struct ifreq dev;
} info;

BYTE* get_permanent_mac(const info *inf) {

    struct ethtool_perm_addr *e_perm_addr;
    struct ifreq ifr;
    BYTE *new_mac;

    new_mac = (BYTE *)malloc(6 * sizeof(BYTE));
    e_perm_addr = (struct ethtool_perm_addr *)malloc(sizeof(struct ethtool_perm_addr) + 6);

    e_perm_addr->cmd = ETHTOOL_GPERMADDR;
    e_perm_addr->size = 6;

    memcpy(&ifr, &(inf->dev), sizeof(struct ifreq));
    ifr.ifr_data = (caddr_t)e_perm_addr;

    if (ioctl(inf->socket, SIOCETHTOOL, &ifr) < 0) {
        perror("ioctl get perm mac");
        return NULL;
    } else {
        for (int i = 0; i < 6; ++i) {
            new_mac[i] = e_perm_addr->data[i];
        }
    }

    return new_mac;
}

int set_mac_address(info *inf, const BYTE* new_mac) {

    for (int i = 0; i < 6; ++i) {
        inf->dev.ifr_hwaddr.sa_data[i] = new_mac[i];
    }

    if (ioctl(inf->socket, SIOCSIFHWADDR, &inf->dev) < 0) {
        perror("ioctl set mac");
        printf("retry with another mac address\n");
        return -1;
    }

    return 0;
}

BYTE* get_mac(const info *inf) {
    BYTE *mac = (BYTE *)malloc(6 * sizeof(BYTE));

    for (int i = 0; i < 6; ++i) {
        mac[i] = inf->dev.ifr_hwaddr.sa_data[i];
    }

    return mac;
}

BYTE* get_random_mac() {
    BYTE *r_mac = (BYTE *)malloc(6 * sizeof(BYTE));

    srand(time(NULL));
    r_mac[0] = rand() % 256;
    r_mac[1] = rand() % 256;
    r_mac[2] = rand() % 256;
    r_mac[3] = rand() % 256;
    r_mac[4] = rand() % 256;
    r_mac[5] = rand() % 256;

    return r_mac;
}

void to_lower(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if ('A' <= s[i] && s[i] <= 'Z')
            s[i] += 'a' - 'A';
    }
}

unsigned char hex_to_char(char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    return c - 'a' + 10;
}

int string_to_mac(char *s, BYTE *mac) {
    if (strlen(s) != 17) {
        printf("incorrect mac address format\n");
        return -1;
    }

    to_lower(s);

    int cnt = 0;
    for (int i = 0; i < 17; ++i) {
        if (s[i] == ':')
            continue;

        mac[cnt] = hex_to_char(s[i]) * 16 + hex_to_char(s[i + 1]);
        ++i;
        ++cnt;
    }

    return 0;
}

char* mac_to_string(const BYTE *mac) {

    char *s = (char *)malloc(18 * sizeof(char));
    sprintf(s, "%2x:%2x:%2x:%2x:%2x:%2x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    s[17] = '\0';

    return s;
}

bool print_current_mac;
bool print_perm_mac;
bool random_mac;
bool reset_to_default;
bool help;
char *interface = NULL;
const char *default_iface = "enp2s0\0";
BYTE *mac;

void iface_down() {
    char *command = (char *)malloc(100 * sizeof(char));
    sprintf(command, "ifconfig %.*s down", (int)strlen(interface), interface);
    system(command);

    free(command);
}

void iface_up() {
    char *command = (char *)malloc(100 * sizeof(char));
    sprintf(command, "ifconfig %.*s up", (int)strlen(interface), interface);
    system(command);

    free(command);
}

void parse_args(int argc, char **argv) {
    int i = 1;

    while (i < argc) {

        if (strncmp(argv[i], "-h", 2) == 0) {
            help = true;
        } else if (strncmp(argv[i], "-p", 3) == 0) {
            print_perm_mac = true;
        } else if (strncmp(argv[i], "-r", 2) == 0) {
            random_mac = true;
        } else if (strncmp(argv[i], "-x", 7) == 0) {
            reset_to_default = true;
        } else if (strncmp(argv[i], "-i", 2) == 0) {
            i++;
            if (argc <= i) {
                printf("no interface name given\n");
                exit(EXIT_FAILURE);
            }
            interface = (char *) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(interface, argv[i]);
        } else {
            mac = (BYTE *)malloc(6 * sizeof(BYTE));
            if (string_to_mac(argv[i], mac) < 0) {
                printf("could not convert the provided string to a valid mac address\n");
                exit(EXIT_FAILURE);
            }
        }

        i++;
    }

    if (argc == 1) {
        print_current_mac = true;
    }

    if (interface == NULL) {
        interface = (char *)malloc((strlen(default_iface) + 1) * sizeof(char));
        strcpy(interface, default_iface);
    }
}

int main(int argc, char **argv) {

    parse_args(argc, argv);

    iface_down();

    info *inf = (info *)malloc(sizeof(info));

    inf->socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (inf->socket < 0) {
        perror("can't create socket");
        iface_up();
        exit(EXIT_FAILURE);
    }
    strcpy(inf->dev.ifr_name, interface);
    if (ioctl(inf->socket, SIOCGIFHWADDR, &inf->dev) < 0) {
        perror("set device name");
        iface_up();
        exit(EXIT_FAILURE);
    }

    if (help) {
        printf ("changemac [options] MAC\n\n"
                "  -h  Print help and exit\n"
                "  -p  Print the permanent and current MAC addresses and exit\n"
                "  -x  Reset to permanent MAC and exit\n"
                "  -r  Random mac\n"
                "  -i  interface (followed by the interface name)\n"
                "  MAC  lowercase or uppercase MAC address to be set\n\n");
        iface_up();
        exit(EXIT_SUCCESS);
    } else if (print_perm_mac) {
        printf("your permanent mac address is: %s\n", mac_to_string(get_permanent_mac(inf)));
        printf("your current mac address is: %s\n", mac_to_string(get_mac(inf)));
    } else if (print_current_mac) {
        printf("your current mac address is: %s\n", mac_to_string(get_mac(inf)));
    } else if (reset_to_default) {
        if (set_mac_address(inf, get_permanent_mac(inf)) < 0) {
            printf("failed to set mac address\n");
            iface_up();
            exit(EXIT_FAILURE);
        }
        printf("mac address set to: %s\n", mac_to_string(get_permanent_mac(inf)));
    } else if (random_mac) {
        BYTE *new_mac = get_random_mac();
        if (set_mac_address(inf, new_mac) < 0) {
            printf("failed to set mac address\n");
            iface_up();
            exit(EXIT_FAILURE);
        }
        printf("mac address set to %s\n", mac_to_string(new_mac));
    } else {
        if (set_mac_address(inf, mac) < 0) {
            printf("failed to set mac address\n");
            iface_up();
            exit(EXIT_FAILURE);
        }
        printf("mac address set to %s\n", mac_to_string(mac));
    }

    iface_up();

    return 0;
}