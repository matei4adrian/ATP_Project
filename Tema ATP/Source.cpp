#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include<string.h>

typedef struct {
    int nr;
    char numeLaptop[30];
    char firma[10];
    char tipStocare[5];
    int memorieInterna;
    int memorieRam;
    char procesor[10];
    char tipPlacaVideo[15];
    char is;
} LAPTOP;

int dimfisier(FILE* f, int dimart)
{
    long poz;
    int dim;

    poz = ftell(f);
    fseek(f, 0, SEEK_END);
    dim = ftell(f) / dimart;
    fseek(f, poz, SEEK_SET);
    return dim;
}

void crearesipopularebinar()
{
    char numefb[20] = "Laptopuri.dat";
    
    FILE* f,* g;
    LAPTOP x;
    int i, cheie, dim;

    fopen_s(&f, numefb, "wb+");

    printf("Numar laptop: ");
    scanf_s("%d", &cheie);
    while (!feof(stdin))
    {
        dim = dimfisier(f, sizeof(LAPTOP));
        if (cheie >= dim)
        {
            x.is = 0;
            fseek(f, 0, SEEK_END);
            for (i = 0; i < cheie - dim; i++)
                fwrite(&x, sizeof(LAPTOP), 1, f);
        }
        fseek(f, cheie * sizeof(LAPTOP), SEEK_SET);
        fread(&x, sizeof(LAPTOP), 1, f);
        if (x.is == 1)
            printf("\nEroare! : Cheia %d exista deja. Introduceti alta cheie! \n", cheie);
        else
        {
            x.nr = cheie;
            printf_s("Nume laptop: ");
            scanf_s("%s", &x.numeLaptop, sizeof(x.numeLaptop));
            printf_s("Firma: ");
            scanf_s("%s", &x.firma, sizeof(x.firma));
            printf_s("Tipul stocarii: ");
            scanf_s("%s", &x.tipStocare, sizeof(x.tipStocare));
            printf_s("Memorie interna (GB): ");
            scanf_s("%d", &x.memorieInterna);
            printf_s("Memorie RAM (GB): ");
            scanf_s("%d", &x.memorieRam);
            printf_s("Producator procesor: ");
            scanf_s("%s", &x.procesor, sizeof(x.procesor));
            printf_s("Tipul placii video: ");
            scanf_s("%s", &x.tipPlacaVideo, sizeof(x.tipPlacaVideo));
            x.is = 1;
            fseek(f, cheie * sizeof(LAPTOP), SEEK_SET);
            fwrite(&x, sizeof(LAPTOP), 1, f);
        }
        printf_s("Numar laptop (sau CTRL+Z): ");
        scanf_s("%d", &cheie);
    }
    
  
    fclose(f);
 

    printf("\nFisierul a fost creat cu succes.\n");

}

void creareFisierText()
{
    char numefb[20] = "Laptopuri.dat";
    char numeft[20] = "Laptopuri.txt";
    FILE* g, * f;
    LAPTOP x;

    fopen_s(&f, numefb, "rb");
    fopen_s(&g, numeft, "wt");
    fprintf_s(g, "%-3s %-30s %-10s %-5s %-5s %-4s %-10s %-15s", "Nr.", "Nume laptop", "Firma", "Tip stocare", "Memorie interna (GB)", "Memorie RAM (GB)", "Procesor", "Tip placa video");
    fseek(f, 0, 0);
    fread(&x, sizeof(LAPTOP), 1, f);

    while (!feof(f))
    {
        if (x.is == 1)
        {
            fprintf_s(g, "\n%-4d %-30s %-10s %-5s %-4d %-3d %-10s %-15s ", x.nr, x.numeLaptop, x.firma, x.tipStocare, x.memorieInterna, x.memorieRam, x.procesor, x.tipPlacaVideo);
        }
        fread(&x, sizeof(LAPTOP), 1, f);
    }

    fclose(f);
    fclose(g);
}

void consultareIntegrala()
{
    char numefb[20] = "Laptopuri.dat";
    FILE* f;
    LAPTOP x;

    fopen_s(&f, numefb, "rb+");
    if (!f)
        printf_s("\nFisierul nu a fost creat inca. Va rugam creati-l!");
    else 
    {
        printf("%-3s %-30s %-10s %-5s %-5s %-4s %-10s %-15s", "Nr.", "Nume laptop", "Firma", "Tip stocare", "Memorie interna (GB)", "Memorie RAM (GB)", "Procesor", "Tip placa video");
        fread(&x, sizeof(LAPTOP), 1, f);

        while (!feof(f))
        {
            if (x.is == 1)
            {
                printf("\n%-4d %-30s %-10s %-5s %-4d %-3d %-10s %-15s ", x.nr, x.numeLaptop, x.firma, x.tipStocare, x.memorieInterna, x.memorieRam, x.procesor, x.tipPlacaVideo);

            }
            fread(&x, sizeof(LAPTOP), 1, f);
        }

        fclose(f);
    }
}

void cautareCheie()
{
    char numefb[20] = "Laptopuri.dat";
    FILE* f;
    LAPTOP x;
    int vb, nrcautat;

    fopen_s(&f, numefb, "rb");
    if (!f)
        printf_s("\nFisierul nu exista inca! Va rugam creati-l!");
    else
    {
        printf_s("\nNumar laptop cautat: ");
        scanf_s("%d", &nrcautat);
        while (!feof(stdin))
        {
            rewind(f);
            vb = 0;
            fread(&x, sizeof(LAPTOP), 1, f);
            while ((!feof(f)) && (!vb))
            {
                if (x.nr == nrcautat)
                {
                    vb = 1;
                    printf("\nNume Laptop: %s, Firma: %s, Tip stocare: %s, Memorie interna: %d, Memorie RAM: %d, Procesor: %s, Tip placa video: %s\n", x.numeLaptop, x.firma, x.tipStocare, x.memorieInterna, x.memorieRam, x.procesor, x.tipPlacaVideo);
                }
                fread(&x, sizeof(LAPTOP), 1, f);
            }
            if (!vb)
                printf("\nNu exista acest laptop.");
            printf("\nIncearca alt numar de laptop: ");
            scanf("%d", &nrcautat);
        }
        fclose(f);
    }
}

void cautareNume() 
{
    char numefb[20] = "Laptopuri.dat";
    FILE* f;
    LAPTOP x;
    int vb;
    char numecautat[30];

    fopen_s(&f, numefb, "rb");
    if (!f)
        printf_s("\nFisierul nu exista inca! Va rugam creati-l!");
    else
    {
        printf_s("\nCauta dupa nume: ");
        scanf_s("%s", &numecautat, sizeof(numecautat));
        while (!feof(stdin))
        {
            rewind(f);
            vb = 0;
            fread(&x, sizeof(LAPTOP), 1, f);
            while ((!feof(f)) && (!vb))
            {
                if (strcmp(x.numeLaptop, numecautat) == 0)
                {
                    vb = 1;
                    printf("\nNume Laptop: %s, Firma: %s, Tip stocare: %s, Memorie interna: %d, Memorie RAM: %d, Procesor: %s, Tip placa video: %s\n", x.numeLaptop, x.firma, x.tipStocare, x.memorieInterna, x.memorieRam, x.procesor, x.tipPlacaVideo);
                }
                fread(&x, sizeof(LAPTOP), 1, f);
            }
            if (!vb)
                printf("\nNu exista acest laptop.");
            printf("\nIncearca alt nume de laptop: ");
            scanf("%s", &numecautat);
        }
        fclose(f);
    }
}

void cautareMultipla()
{

    char numefb[20] = "Laptopuri.dat";
    FILE* f;
    LAPTOP x;
    int vb, i;
    char tipStocareCautata[5];

    fopen_s(&f, numefb, "rb");
    if (!f)
        printf_s("\nFisierul nu exista inca! Va rugam creati-l!");
    else
    {
        printf_s("\nCauta laptopurile dupa tipul de stocare: ");
        scanf_s("%s", &tipStocareCautata, sizeof(tipStocareCautata));
        while (!feof(stdin))
        {
            rewind(f);
            fread(&x, sizeof(LAPTOP), 1, f);
            vb = 0;
            while (!feof(f))
            {
                if (strcmp(x.tipStocare, tipStocareCautata) == 0)
                {
                    printf("\nNume Laptop: %s, Firma: %s, Tip stocare: %s, Memorie interna: %d, Memorie RAM: %d, Procesor: %s, Tip placa video: %s\n", x.numeLaptop, x.firma, x.tipStocare, x.memorieInterna, x.memorieRam, x.procesor, x.tipPlacaVideo);
                }
                fread(&x, sizeof(LAPTOP), 1, f);
                vb = 1;
            }
            if (!vb)
                printf("\nNu exista aceste laptopuri.");
            printf("\nIncearca alt tip de stocare: ");
            scanf("%s", &tipStocareCautata);
        }
        fclose(f);
    }
}

void modificareDupaCheie()
{
    char numefb[20] = "Laptopuri.dat";
    FILE* f;
    LAPTOP x;
    int vb;
    int numarCautat;
    int memorieInternaNoua;

    fopen_s(&f, numefb, "rb+");
    if (!f)
        printf_s("\nFisierul nu a fost creat inca. Va rugam creati-l!");
    else
    {
        printf_s("\nNumar laptop cautat: ");
        scanf_s("%d", &numarCautat);
        while (numarCautat != 0 && !feof(stdin))
        {
            rewind(f);
            vb = 0;
            fread(&x, sizeof(LAPTOP), 1, f);
            while (!feof(f) && !vb)
            {
                if (x.nr == numarCautat)
                {
                    vb = 1;

                    printf("\nNume laptop: %s, Tip Stocare: %s, Memorie Interna (GB): %d\n", x.numeLaptop, x.tipStocare, x.memorieInterna);

                    printf_s("\nMemorie interna noua (GB): ");
                    scanf_s("%d", &memorieInternaNoua);
                    if (memorieInternaNoua != 0 && memorieInternaNoua >= 128)
                    {
                        x.memorieInterna = memorieInternaNoua;
                        printf("\nModificare efectuata cu succes!");
                        printf("\nNume laptop: %s, Tip Stocare: %s, Memorie Interna (GB): %d\n", x.numeLaptop, x.tipStocare, x.memorieInterna);
                        fseek(f, ftell(f) - sizeof(LAPTOP), 0);
                        fwrite(&x, sizeof(LAPTOP), 1, f);
                        fseek(f, 0, 1);
                    }
                }
                fread(&x, sizeof(LAPTOP), 1, f);
            }
            if (!vb)
                printf_s("\nLaptopul nu exista!");
            printf_s("\nIncercati alt numar de laptop (intoduceti 0 pentru a reveni la meniu): ");
            scanf_s("%d", &numarCautat);
        }
        fclose(f);
    }
}

void modificareDupaCamp()
{
    char numefb[20] = "Laptopuri.dat";
    FILE* f;
    LAPTOP x;
    int vb;
    char numeLaptopCautat[30];
    char tipStocareNou[4];
    char nimic[4] = " ";

    fopen_s(&f, numefb, "rb+");
    if (!f)
        printf_s("\nFisierul nu a fost creat inca. Va rugam creati-l!");
    else
    {
        printf_s("\nNumele laptopului cautat: ");
        scanf_s("%s", &numeLaptopCautat, sizeof(numeLaptopCautat));
        while (!feof(stdin))
        {
            rewind(f);
            vb = 0;
            fread(&x, sizeof(LAPTOP), 1, f);
            while (!feof(f) && !vb)
            {
                if (strcmp(x.numeLaptop, numeLaptopCautat) == 0)
                {
                    vb = 1;

                    printf("\nNume laptop: %s, Firma: %s, Tip stocare: %s\n", x.numeLaptop, x.firma, x.tipStocare);

                    printf_s("\nTip stocare nou: ");
                    scanf_s("%s", &tipStocareNou, sizeof(tipStocareNou));
                    if (tipStocareNou == "SSD" || tipStocareNou == "HDD")
                    {
                        strcpy(x.tipStocare, tipStocareNou); 
                        printf("\nModificare efectuata cu succes!");
                        printf("\nNume laptop: %s, Firma: %s, Tip stocare: %s\n", x.numeLaptop, x.firma, x.tipStocare);
                        fseek(f, ftell(f) - sizeof(LAPTOP), 0);
                        fwrite(&x, sizeof(LAPTOP), 1, f);
                        fseek(f, 0, 1);
                    }
                }
                fread(&x, sizeof(LAPTOP), 1, f);
            }
            if (!vb)
                printf_s("\nLaptopul nu exista!");
            printf_s("\nIncercati alt nume de laptop: ");
            scanf_s("%s", &numeLaptopCautat, sizeof(numeLaptopCautat));
        }
        fclose(f);
    }
}

void modificareMultiplaDupaCamp()
{
    char numefb[20] = "Laptopuri.dat";
    FILE* f;
    LAPTOP x;
    char tipPlacaVideoCautata[10];
    char tipStocareNou[4];
    int vb = 0;

    fopen_s(&f, numefb, "rb+");
    if (!f)
        printf_s("\nFisierul nu a fost creat inca. Va rugam creati-l!");
    else
    {
        printf_s("\nTipul placii video cautata: ");
        scanf_s("%s", &tipPlacaVideoCautata, sizeof(tipPlacaVideoCautata));
        while (!feof(stdin))
        {
            rewind(f);
            fread(&x, sizeof(LAPTOP), 1, f);
            printf_s("\nTip stocare nou: ");
            scanf_s("%s", &tipStocareNou, sizeof(tipStocareNou));
            while (!feof(f))
            {
                if (strcmp(x.tipPlacaVideo, tipPlacaVideoCautata) == 0)
                {
                    if (strcmp(tipStocareNou, "SSD") == 0 || strcmp(tipStocareNou, "HDD") == 0)
                    {
                        strcpy(x.tipStocare, tipStocareNou);
                        printf("\nStocare modificata leptopului:");
                        printf("\nNume laptop: %s, Tip stocare: %s,  Tip placa video: %s, \n", x.numeLaptop, x.tipStocare, x.tipPlacaVideo);
                        
                        fseek(f, ftell(f) - sizeof(LAPTOP), 0);
                        fwrite(&x, sizeof(LAPTOP), 1, f);
                        fseek(f, 0, 1);
                        vb = 1;
                    }
                }
                
                fread(&x, sizeof(LAPTOP), 1, f);
                
            }
            if (!vb)
                printf_s("\nNu exista niciun laptop cu acest tip de placa video!");
            printf_s("\nModificati in functie de alt tip de placa video: ");
            scanf_s("%s", &tipPlacaVideoCautata, sizeof(tipPlacaVideoCautata));
        }
        fclose(f);
    }
}

void meniu()

{
    printf("\nAlegeti o operatie:\n");
    printf("1. Creare fisier binar\n");
    printf("2. Creare sau actualizare fisier text\n");
    printf("3. Afisare lista laptopuri\n");
    printf("4. Cautare laptop dupa cheie \n");
    printf("5. Cautare laptop dupa nume\n");
    printf("6. Cautare laptopuri dupa tipul de stocare\n");
    printf("7. Modificare memorie interna in functie de cheia introdusa\n");
    printf("8. Modificare tip stocare in functie de numele laptopului cautat\n");
    printf("9. Modificare tip stocare in tuturor laptopurilor cu o anumita placa video\n");
}

void main()
{
    FILE* f;
    int opt;


    meniu();
    printf("Introduceti optiunea: ");
    scanf_s("%d", &opt);

    while (opt)
    {
        switch (opt)
        {
        case 1:
            printf("Ati ales sa creati fisierul binar\n");
            crearesipopularebinar();
            break;
        case 2:
            printf("Ati ales sa creati sau sa actualizati fisierul text\n");
            creareFisierText();
            break;
        case 3:
            printf("Ati ales afisati lista cu laptopuri\n");
            consultareIntegrala();
            break;
        case 4:
            printf("Ati ales sa cautati un laptop dupa cheie\n");
            cautareCheie();
            break;
        case 5:
            printf("Ati ales sa cautati un laptop dupa nume\n");
            cautareNume();
            break;
        case 6:
            printf("Ati ales sa cautati laptopuri dupa tipul de stocare\n");
            cautareMultipla();
            break;
        case 7:
            printf("Ati ales sa modificati campul memoriei interne introducand o cheie\n");
            modificareDupaCheie();
            break;
        case 8:
            printf("Ati ales sa modificati campul tipului de stocare introducand numle unui laptop\n");
            modificareDupaCamp();
            break;
        case 9:
            printf("Ati ales sa modificati campul tipului de stocare a tuturor laptopurilor cu o anumita placa video\n");
            modificareMultiplaDupaCamp();
            break;
        default:
            printf("Optiune inexistenta! Reincearcati!\n");
            break;
        }

        meniu();
        printf("Introduceti optiunea: ");
        scanf_s("%d", &opt);

    }

    _getch();

}