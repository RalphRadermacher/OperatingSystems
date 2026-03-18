/* -------------------------------------------------------------------------- */

/*
 * Vorlesung Betriebssysteme an der DHBW Karlsruhe und Mannheim
 *
 * Dozent: Dr. Ralph Radermacher
 */

/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_CPUS 256

/* -------------------------------------------------------------------------- */

void print_header ()
{
    printf ("╔════════════════════════════════════════════════════════════════╗\n");
    printf ("║           Linux Interrupt-Statistiken Monitor                  ║\n");
    printf ("╚════════════════════════════════════════════════════════════════╝\n\n");
}

void print_separator (int width)
{
    printf ("├");
    for (int i = 0; i < width - 2; i++)
    {
        printf ("─");
    }
    printf ("┤\n");
}

void print_box_line (const char *label, const char *value)
{
    printf ("│ %-20s : %-38s │\n", label, value);
}

/* -------------------------------------------------------------------------- */

int main ()
{
    FILE *fp;
    char line[MAX_LINE];
    char irq[32], type[128], desc[256];
    long long counts[MAX_CPUS];
    int num_cpus = 0;
    int line_num = 0;

    // Öffne /proc/interrupts

    if ((fp = fopen ("/proc/interrupts", "r")) == NULL)
    {
        perror ("Fehler beim Öffnen von /proc/interrupts");
        return 1;
    }

    print_header ();

    // Lese erste Zeile (CPU-Header)
    //
    //             CPU0       CPU1       CPU2       CPU3       CPU4       CPU5       CPU6       CPU7

    if (fgets (line, sizeof(line), fp))
    {
        char *token = strtok (line, " \t\n");

        while (token != NULL && num_cpus < MAX_CPUS)
        {
            if (strncmp (token, "CPU", 3) == 0)
            {
                num_cpus++;
            }
            token = strtok (NULL, " \t\n");
        }
    }

    printf ("┌────────────────────────────────────────────────────────────────┐\n");
    printf ("│ System-Info: %d CPU-Kern(e) erkannt                            │\n", num_cpus);
    printf ("└────────────────────────────────────────────────────────────────┘\n\n");

    printf ("┌────────┬──────────────┬──────────────────────────────────────────┐\n");
    printf ("│  IRQ   │   Anzahl     │  Beschreibung                            │\n");
    printf ("├────────┼──────────────┼──────────────────────────────────────────┤\n");

    // Lese Interrupt-Zeilen
    //
    // LOC:     283437     281906     264200     249929     211548     377578     231131     246507   Local timer interrupts

    while (fgets (line, sizeof(line), fp))
    {
        line_num++;

        // Parse die Zeile
        char *ptr   = line;
        char *colon = strchr (line, ':');

        if (colon == NULL)
            continue;

        // Extrahiere IRQ-Nummer
        *colon = '\0';
        sscanf (ptr, "%s", irq);

        // Extrahiere Counts
        ptr = colon + 1;
        long long total_count = 0;

        for (int i = 0; i < num_cpus && i < MAX_CPUS; i++)
        {
            if (sscanf (ptr, "%lld", &counts[i]) == 1)
            {
                total_count += counts[i];
                // Überspringe zur nächsten Zahl
                while (*ptr == ' ' || *ptr == '\t')
                    ptr++;
                while (*ptr >= '0' && *ptr <= '9')
                    ptr++;
            }
        }

        // Extrahiere Beschreibung (Rest der Zeile)
        while (*ptr == ' ' || *ptr == '\t')
            ptr++;

        // Entferne Newline
        size_t len = strlen (ptr);
        if (len > 0 && ptr[len - 1] == '\n')
        {
            ptr[len - 1] = '\0';
        }

        // Kürze Beschreibung wenn zu lang
        if (strlen (ptr) > 40)
        {
            ptr[37] = '.';
            ptr[38] = '.';
            ptr[39] = '.';
            ptr[40] = '\0';
        }

        // Gib formatierte Zeile aus
        printf ("│ %-6s │ %12lld │ %-40s │\n", irq, total_count, ptr);
    }

    printf ("└────────┴──────────────┴──────────────────────────────────────────┘\n");

    fclose (fp);

    return 0;
}

/* -------------------------------------------------------------------------- */


