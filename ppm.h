#ifndef PPM_H
#define PPM_H

//Description : Cette structure représente un pixel dans une image PPM, avec les valeurs des canaux rouge, vert et bleu.
struct ppm_pixel {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

//Description : Définit la couleur d'un pixel aux coordonnées (x, y) dans l'image.
static inline void ppm_setpixel(struct ppm_pixel *px, unsigned char r,
                                unsigned char g, unsigned char b) {
  px->r = r;
  px->g = g;
  px->b = b;
}

//Description : Cette structure représente une image au format PPM, avec sa largeur, sa hauteur et un tableau de pixels.
struct ppm_image {
  unsigned int width;
  unsigned int height;
  struct ppm_pixel *px;
};

//Description : Initialise une structure ppm_image avec la largeur w et la hauteur h, alloue la mémoire pour les pixels.
int ppm_image_init(struct ppm_image *im, int w, int h);
//Description : Libère la mémoire allouée pour les pixels de l'image.
int ppm_image_release(struct ppm_image *im);

//Description :  Définit la couleur d'un pixel dans l'image aux coordonnées (x, y) avec les valeurs RGB spécifiées.
static inline void ppm_image_setpixel(struct ppm_image *im, int x, int y,
                                      unsigned char r, unsigned char g,
                                      unsigned char b) {
  struct ppm_pixel *px = im->px + im->width * y + x;
  ppm_setpixel(px, r, g, b);
}

//Description : Ecrit l'image img au format PPM dans un fichier.
int ppm_image_dump(struct ppm_image *im, char *path);

#endif /* PPM_H */