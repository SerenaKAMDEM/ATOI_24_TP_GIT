#include "ppm.h"
 
 
int main(int argc, char *argv[])
{   
    //Création d'une image PPM de 1024x1024 pixels
    struct ppm_image im;
 
    ppm_image_init( &im, 1024, 1024 );
 
    int i,j;
    
    // Parcours de chaque pixel de l'image pour lui attribuer une couleur basée sur sa position
    for (i = 0; i < 1024; ++i) {
        for (j = 0; j < 1024; ++j) {
            // Attribution d'une couleur basée sur la position (i, j) du pixel
            // Les couleurs varient en fonction des valeurs de i et j modulo 255
            ppm_image_setpixel( &im, i, j, i%255, j%255, (i+j)%255);
        }
    }
    
       // Parcours de la diagonale de l'image pour attribuer une couleur rouge
    for (i = 0; i < 1024; ++i) {
           // Les pixels sur la diagonale ont la couleur rouge (255, 0, 0)
        ppm_image_setpixel( &im, i, i, 255, 0, 0 );
    }
 
     // Sauvegarde de l'image générée dans un fichier "test.ppm"
    ppm_image_dump( &im , "test.ppm");
  
    // Libération de la mémoire allouée pour l'image
    ppm_image_release( &im );
 
 
    return 0;
}