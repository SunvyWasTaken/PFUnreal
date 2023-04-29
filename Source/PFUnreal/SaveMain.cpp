#include "SaveMain.h"

// Définit les valeurs par défaut
USaveMain::USaveMain()
{
	// Définissez ce empty pour appeler Tick() à chaque frame. Vous pouvez désactiver cette option pour améliorer les performances si vous n’en avez pas besoin.
	Levels.Add("L_Level1", FDataGame());
	Levels.Add("L_Level2", FDataGame());
	Levels.Add("L_Level3", FDataGame());
	Levels.Add("L_AITestMap", FDataGame());
}


