

MLV_Color clanToColor(char clan){
	switch(clan){
		case ROUGE :
			return MLV_COLOR_RED;
		case BLEU :
			return MLV_COLOR_BLUE;
		default:
			printf("error clan : %c\n", clan);
			return MLV_COLOR_BLUE;
	}
}


void drawIn(char* file, int largeur, int hauteur, int x, int y, char clan, char genre){
	MLV_Image *image;
	image = MLV_load_image(file);
	MLV_resize_image_with_proportions( image, largeur/2, hauteur/2);
	switch(genre){
		case CHATEAU:
			MLV_draw_image( image, (y*largeur)+10, (x*hauteur)+10);
			MLV_draw_rectangle((y*largeur)+10, (x*hauteur)+10, largeur, hauteur, clanToColor(clan));
			break;
		case GUERRIER:
			MLV_draw_image( image, (y*largeur)+10, (x*hauteur)+(hauteur/2)+10);
			break;
		case MANANT:
			MLV_draw_image( image, (y*largeur)+(largeur/2)+10, (x*hauteur)+(hauteur/2)+10);	
			break;
		case BARON:
			MLV_draw_image( image, (y*largeur)+(largeur/2)+10, (x*hauteur)+10);
			break;
		default:
			printf("ERROR\n");
			break;
	}
}


void drawBoxes(){

	MLV_draw_text_box(L_FENETRE-225, H_FENETRE-700, 150, 30, "Attendre", 9,  MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK,  MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(L_FENETRE-225, H_FENETRE-650, 150, 30, "Produire Baron", 9,  MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK,  MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(L_FENETRE-225, H_FENETRE-600, 150, 30, "Produire Guerrier", 9,  MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK,  MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(L_FENETRE-225, H_FENETRE-550, 150, 30, "Produire Manant" , 9,  MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK,  MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(L_FENETRE-200, H_FENETRE-100, 150, 30, "Sauvegarder" , 9, MLV_COLOR_DARKSLATEGRAY1, MLV_COLOR_BLACK, MLV_COLOR_DARKSLATEGRAY1, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(L_FENETRE-200, H_FENETRE-50, 150, 30, "Quitter" , 9, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
}


int drawBoxesAgent(Agent * agent, int tresor){
	
	int x, y;
	MLV_draw_text_box(L_FENETRE-225, H_FENETRE-700, 150, 30, "Immobile", 9, MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK, MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(L_FENETRE-225, H_FENETRE-650, 150, 30, "Déplacer", 9, MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK, MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(L_FENETRE-200, H_FENETRE-100, 150, 30, "Sauvegarder" , 9, MLV_COLOR_DARKSLATEGRAY1, MLV_COLOR_BLACK, MLV_COLOR_DARKSLATEGRAY1, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(L_FENETRE-200, H_FENETRE-50, 150, 30, "Quitter" , 9, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

	if(agent->genre == MANANT && tresor >= CGUERRIER)
		MLV_draw_text_box(L_FENETRE-225, H_FENETRE-600, 150, 30, "Devenir Guerrier", 9, MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK, MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	else if(agent->genre == BARON && tresor >= CCHATEAU)
		MLV_draw_text_box(L_FENETRE-225, H_FENETRE-600, 150, 30, "Construire Chateau", 9, MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK, MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

	MLV_actualise_window();
	MLV_wait_mouse(&x, &y);

	//Bouton rester immobile
	if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-670 && y > H_FENETRE-700))
		return 1;
	//Bouton Déplacer
	else if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-620 && y > H_FENETRE-650))
		return 2;
	//Devenir Guerrier
	else if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-570 && y > H_FENETRE-600) && agent->genre == MANANT)
		return 3;
	//Construire Baron
	else if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-570 && y > H_FENETRE-600) && agent->genre == BARON)
		return 5;
	//Sauvegarder
	else if((x < L_FENETRE-50 && x > L_FENETRE-200) && (y < H_FENETRE-70 && y > H_FENETRE-100))
		return 4;
	//Quitter
	else if((x < L_FENETRE-50 && x > L_FENETRE-200) && (y < H_FENETRE-20 && y > H_FENETRE-50))
		exit(EXIT_FAILURE);	
	return 0;
}

int drawBoxesAttaque(Agent *agent, int tresor){

	int x, y;

	MLV_draw_text_box(L_FENETRE-225, H_FENETRE-600, 150, 30, "Attaquer" , 9, MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK, MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);	
	MLV_draw_text_box(L_FENETRE-225, H_FENETRE-650, 150, 30, "Passer", 9, MLV_COLOR_BLUEVIOLET, MLV_COLOR_BLACK, MLV_COLOR_BLUEVIOLET, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
	MLV_wait_mouse(&x, &y);
	
	//Attaquer
	if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-570 && y > H_FENETRE-600) && (agent->genre == GUERRIER || agent->genre == BARON))
		return 1;
	else if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-620 && y > H_FENETRE-650))
		return 2;
	return 0;
}

void drawArray(Monde world){
	int x, y;
	AListe curs = NULL;
	int largeur = 60, hauteur = 60;
	
	for (x = 0 ; x < NBLIG ; x++) {
		for (y = 0 ; y < NBCOL ; y++) {
			Agent* habitant = world.plateau[x][y].habitant;
			//haut gauche
			MLV_draw_rectangle((y*largeur)+10, (x*hauteur)+10, largeur/2, hauteur/2, MLV_rgba(120,120,120,255));
			//haut droit
			MLV_draw_rectangle((y*largeur)+(largeur/2)+10, (x*hauteur)+10, largeur/2, hauteur/2, MLV_rgba(120,120,120,255));
			//bas gauche
			MLV_draw_rectangle((y*largeur)+10, (x*hauteur)+(hauteur/2)+10, largeur/2, hauteur/2, MLV_rgba(120,120,120,255));
			//bas droit
			MLV_draw_rectangle((y*largeur)+(largeur/2)+10, (x*hauteur)+(hauteur/2)+10, largeur/2, hauteur/2, MLV_rgba(120,120,120,255));
			//gros rectangle
			MLV_draw_rectangle((y*largeur)+10, (x*hauteur)+10, largeur, hauteur, MLV_COLOR_WHITE);
			if(world.plateau[x][y].clan == ROUGE)
				MLV_draw_rectangle((y*largeur)+10, (x*hauteur)+10, largeur, hauteur, MLV_COLOR_RED);
			else if(world.plateau[x][y].clan == BLEU)
				MLV_draw_rectangle((y*largeur)+10, (x*hauteur)+10, largeur, hauteur, MLV_COLOR_BLUE);

				//CHATEAU
			if (world.rouge != NULL){
				for(curs = world.rouge; curs != NULL; curs=curs->vsuiv){
					drawIn( "image/castleR.png", largeur, hauteur, curs->posx, curs->posy, curs->clan, curs->genre);
				}
			}
			if(world.bleu != NULL){
				for(curs = world.bleu; curs != NULL; curs=curs->vsuiv){
					drawIn( "image/castleB.png", largeur, hauteur, curs->posx, curs->posy, curs->clan, curs->genre);
				}
			}
		
			if (habitant != NULL){
				switch(habitant->genre){
					case GUERRIER:
						if (habitant->clan == ROUGE)
							drawIn("image/guerrierR.png", largeur, hauteur, habitant->posx, habitant->posy, habitant->clan, habitant->genre);
						else
							drawIn("image/guerrierB.png", largeur, hauteur, habitant->posx, habitant->posy, habitant->clan, habitant->genre);
						break;
					case MANANT:
						if (habitant->clan == ROUGE)
							drawIn("image/manantR.png", largeur, hauteur, habitant->posx, habitant->posy, habitant->clan, habitant->genre);
						else
							drawIn("image/manantB.png", largeur, hauteur, habitant->posx, habitant->posy, habitant->clan, habitant->genre);
						break;
					case BARON:
						if (habitant->clan == ROUGE)
							drawIn("image/baronR.png", largeur, hauteur, habitant->posx, habitant->posy, habitant->clan, habitant->genre);
						else
							drawIn("image/baronB.png", largeur, hauteur, habitant->posx, habitant->posy, habitant->clan, habitant->genre);
						break;
					default:
						printf("ERR\n");
						break;
				}
			}
		}
	}
}


int clikBoxes(){
	
	int x, y;
	while(1){
		MLV_wait_mouse(&x, &y);
		//Bouton Attendre
		if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-670 && y > H_FENETRE-700))
			return 'a';
		//Bouton Produire Baron
		else if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-620 && y > H_FENETRE-650))
			return BARON;
		//Bouton Produire Guerrier
		else if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-570 && y > H_FENETRE-600))
			return GUERRIER;
		//Bouton Produire Manant
		else if((x < L_FENETRE-75 && x > L_FENETRE-225) && (y < H_FENETRE-520 && y > H_FENETRE-550))
			return MANANT;
		else if((x < L_FENETRE-50 && x > L_FENETRE-200) && (y < H_FENETRE-70 && y > H_FENETRE-100))
			return 's';	
		//Bouton Quitter
		else if((x < L_FENETRE-50 && x > L_FENETRE-200) && (y < H_FENETRE-20 && y > H_FENETRE-50)){
			exit(EXIT_FAILURE);
		}
	}
}


void drawInformation(char couleur, Monde world){
	
	MLV_draw_text(L_FENETRE-220,20,"       Tour %d",MLV_COLOR_WHITE,world.tour);
	MLV_draw_text(L_FENETRE-250,30,"_____________________________",MLV_COLOR_WHITE);
	MLV_draw_text(L_FENETRE-250,60, "Tour joueur",MLV_COLOR_WHITE);
	if(couleur == ROUGE){
		MLV_draw_text(L_FENETRE-150,60, "ROUGE",MLV_COLOR_RED);
		MLV_draw_text(L_FENETRE-250,80, "Tresor : %d",MLV_COLOR_WHITE,world.tresorRouge);
	}
	else if(couleur == BLEU){
		MLV_draw_text(L_FENETRE-150,60, "BLEU",MLV_COLOR_BLUE);
		MLV_draw_text(L_FENETRE-250,80, "Tresor : %d",MLV_COLOR_WHITE,world.tresorBleu);
	}
	MLV_actualise_window();
}


void actuMonde(Monde world, char couleur ){
	
	MLV_clear_window(MLV_COLOR_BLACK);
	drawArray(world);
	drawInformation(couleur, world);
	MLV_actualise_window();
}

