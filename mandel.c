#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"
 

// Seuil pour la valeur absolue du nombre complexe 
#define TRSH 2.0
// Nombre maximum d'itérations pour chaque point
#define ITER 1024ull
 
 // Dimensions de l'image
#define SIZEX 1500
#define SIZEY 1500
 
 //fonction pour  Calculer la partie réelle de la constante c pour un pixel à la position x sur l'axe des abscisses.
double cx( int x )
{    //Calcule le facteur de conversion pour passer de l'index des pixels à la valeur correspondante dans le plan complexe.
    /* -2 ---> 1 */
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 +  x * qx;
}
 
 //Fonction pour Calculer la partie imaginaire de la constante c pour un pixel à la position y sur l'axe des ordonnées.
double cy( int y )
{    //Calcule le facteur de conversion pour passer de l'index des pixels à la valeur correspondante dans le plan complexe.
    /* -1 ---> 1 */
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}
 
 // Fonction principale du programme
int main(int argc, char *argv[])
{    //Structure pour stocker une image au format PPM.
    struct ppm_image im;
    //Initialise une image PPM avec une largeur w et une hauteur h.
    ppm_image_init( &im , SIZEX , SIZEY );
 
    int i,j;
    double colref = 255.0/log(ITER);
    
    //Boucle pour parcourir chaque pixel de l'image
    for (i = 0; i < SIZEX; ++i) {
        for (j = 0; j < SIZEY; ++j) {
 
            unsigned long int iter = 0;
            
            // Calcul de la constante c pour le pixel actuel
            double complex c =  cx(i) + cy(j) * I;
            double complex z = 0;
            
            // Boucle pour itérer jusqu'à la limite d'itérations ou que |z| dépasse le seuil
            while(iter < ITER)
            {
                double mod = cabs(z);
                // Condition de sortie si |z| dépasse le seuil
                if( TRSH < mod )
                {
                    break;
                }
                // Calcul de la prochaine itération de z selon la formule de Mandelbrot
                z = z*z + c;
               // Incrémentation du nombre d'itérations
                iter++;
            }
 
            // Calcul de la valeur de gris pour le pixel en fonction du nombre d'itérations
            int grey = colref*log(iter);

            // Définition de la couleur du pixel dans l'image
            ppm_image_setpixel(&im, i,j, grey, grey , grey );
        }
    }
 
    // Sauvegarde de l'image dans un fichier PPM
    ppm_image_dump( &im, "m.ppm");
    //Libération de la mémoire allouée pour l'image
    ppm_image_release( &im );
 
 
    return 0;
}