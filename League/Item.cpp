#pragma once
#include "Item.h"

Item::Item()
{
	name = "N/A";
	descriptionstring.clear();
	descriptionuniquestring.clear();
	buildsinto.clear();
	childrenitems.clear();
	image = 0;
	descriptionimage = 0;
	buyimage = 0;
	LIFESTEAL = 0;
	AD = 0;
	AP = 0;
	MR = 0;
	ARMOR = 0;
	ATKSPEED = 0;
	CRIT = 0;
	CDR = 0;
	HEALTHREGEN = 0;
	HEALTH = 0;
	MAGICPEN = 0;
	MOVESPEED = 0;
	GREVIOUSWOUNDS = 0;
	UNIQUEPASSIVEPD = 0;
	UNIQUEPASSIVEIF = 0;
	UNIQUEPASSIVERO = 0;
	UNIQUEPASSIVEBT = 0;
	UNIQUEPASSIVEWA = 0;
	COST = 0;
	SELLCOST = 0;
}
void Item::ItemReset()
{
	name = "N/A";
	descriptionstring.clear();
	descriptionuniquestring.clear();
	buildsinto.clear();
	childrenitems.clear();
	image = 0;
	descriptionimage = 0;
	buyimage = 0;
	LIFESTEAL = 0;
	AD = 0;
	AP = 0;
	MR = 0;
	ARMOR = 0;
	ATKSPEED = 0;
	CRIT = 0;
	CDR = 0;
	HEALTHREGEN = 0;
	HEALTH = 0;
	MAGICPEN = 0;
	MOVESPEED = 0;
	GREVIOUSWOUNDS = 0;
	UNIQUEPASSIVEPD = 0;
	UNIQUEPASSIVEIF = 0;
	UNIQUEPASSIVERO = 0;
	UNIQUEPASSIVEBT = 0;
	UNIQUEPASSIVEWA = 0;
	COST = 0;
	SELLCOST = 0;
}
void Item::BuildBloodThirster()
{
	ItemReset();
	extern SDL_Texture* ImageBloodThirster;
	image = ImageBloodThirster;
	name = "Blood_Thirster";
	descriptionstring.push_back("+80 Attack Damage");
	descriptionstring.push_back("+20% Life Steal");
	descriptionuniquestring.push_back("UNIQUE Passive - Your life steal");
	descriptionuniquestring.push_back("overheals you, converting the excess");
	descriptionuniquestring.push_back("healing into a shield that absorbs up to");
	descriptionuniquestring.push_back("50 - 350 (based on level) a shield that");
	descriptionuniquestring.push_back("absorbs up to 50 - 350 (based on level)");
	descriptionuniquestring.push_back("damage and decays when out-of-combat for");
	descriptionuniquestring.push_back("25 seconds");
	childrenitems.push_back("BF_Sword");
	AD = 80;
	LIFESTEAL = 20;
	UNIQUEPASSIVEBT = true;
	COST = 3500;
	SELLCOST = 2450;
}
void Item::BuildInfinityEdge()
{
	ItemReset();
	extern SDL_Texture* Infinityedgeimage;
	image = Infinityedgeimage;
	name = "Infinity_Edge";
	descriptionstring.push_back("+80 Attack Damage");
	descriptionstring.push_back("+25% critical strike chance");
	descriptionuniquestring.push_back("UNIQUE Passive - Critical strikes deal");
	descriptionuniquestring.push_back("225% damage instead of 200%.");
	childrenitems.push_back("BF_Sword"); childrenitems.push_back("Pickaxe"); childrenitems.push_back("Cloak_of_Agility");
	AD = 80;
	CRIT = 25;
	UNIQUEPASSIVEIF = true;
	COST = 3400;
	SELLCOST = 425;
}
void Item::BuildBfSword()
{
	ItemReset();
	extern SDL_Texture* ImageBfSword;
	image = ImageBfSword;
	name = "BF_Sword";
	descriptionstring.push_back("+40 Attack Damage");
	buildsinto.push_back("Infinity_Edge");
	AD = 40;
	COST = 1300;
	SELLCOST = 1300;
}
void Item::BuildPickAxe()
{
	ItemReset();
	extern SDL_Texture* ImagePickAxe;
	image = ImagePickAxe;
	name = "Pickaxe";
	descriptionstring.push_back("+25 Attack Damage");
	buildsinto.push_back("Infinity_Edge");
	AD = 25;
	COST = 875;
	SELLCOST = 875;
}
void Item::BuildClockAgility()
{
	ItemReset();
	extern SDL_Texture* ImageClockAgility;
	image = ImageClockAgility;
	name = "Cloak_of_Agility";
	descriptionstring.push_back("+20% Critical Strike Chance");
	buildsinto.push_back("Infinity_Edge");
	CRIT = 20;
	COST = 800;
	SELLCOST = 800;
}
void Item::BuildMorrello()
{
	ItemReset();
	extern SDL_Texture* ImageMorrello;
	image = ImageMorrello;
	name = "Morellonomicon";
	descriptionstring.push_back("+70 Attack Power");
	descriptionstring.push_back("+300 Health");
	descriptionstring.push_back("+15% Magic Penetration");
	descriptionuniquestring.push_back("UNIQUE Passive - Magic damage dealt to");
	descriptionuniquestring.push_back("champions inflects them with");
	descriptionuniquestring.push_back("Grevious Wounds for 3 seconds.");
	childrenitems.push_back("Oblivion_Orb"); childrenitems.push_back("Blasting_Wand");
	AP = 70;
	HEALTH = 300;
	GREVIOUSWOUNDS = true;
	MAGICPEN = 15;
	COST = 3000;
	SELLCOST = 550;
}
void Item::BuildBlastingRod()
{
	ItemReset();
	extern SDL_Texture* ImageBlastingRod;
	image = ImageBlastingRod;
	name = "Blasting_Wand";
	descriptionstring.push_back("+40 Attack Power");
	buildsinto.push_back("Morellonomicon");
	AP = 40;
	COST = 850;
	SELLCOST = 850;
}
void Item::BuildOblivionOrb()
{
	ItemReset();
	extern SDL_Texture* ImageOblivionOrb;
	image = ImageOblivionOrb;
	name = "Oblivion_Orb";
	descriptionstring.push_back("+20 Ability Power");
	descriptionstring.push_back("+200 Health");
	descriptionstring.push_back("+15% Magic Penetration");
	buildsinto.push_back("Morellonomicon");
	childrenitems.push_back("Ruby_Crystal"); childrenitems.push_back("Amplifying_Tome");
	AP = 20;
	HEALTH = 200;
	MAGICPEN = 15;
	COST = 1600;
	SELLCOST = 765;
}
void Item::BuildAmplifyingTome()
{
	ItemReset();
	extern SDL_Texture* ImageAmplifyingTome;
	image = ImageAmplifyingTome;
	name = "Amplifying_Tome";
	descriptionstring.push_back("+20 Attack Power");
	buildsinto.push_back("Oblivion_Orb");
	AP = 20;
	COST = 435;
	SELLCOST = 435;
}
void Item::BuildRubyCrystal()
{
	ItemReset();
	extern SDL_Texture* ImageRubyCrystal;
	image = ImageRubyCrystal;
	name = "Ruby_Crystal";
	descriptionstring.push_back("+ 150 Health");
	buildsinto.push_back("Oblivion_Orb"); buildsinto.push_back("Spectres_Cowl"); buildsinto.push_back("Giants_Belt"); buildsinto.push_back("Crystalline_Bracer");
	HEALTH = 150;
	COST = 400;
	SELLCOST = 400;
}
void Item::BuildPhantomDancer()
{
	ItemReset();
	extern SDL_Texture* ImagePhantomDancer;
	image = ImagePhantomDancer;
	name = "Phantom_Dancer";
	descriptionstring.push_back("+30% Attack Speed");
	descriptionstring.push_back("+25% Critical Strike Chance");
	descriptionstring.push_back("+5 Movement Speed");
	descriptionuniquestring.push_back("UNIQUE Passive - If you would take");
	descriptionuniquestring.push_back("damage that would reduce your Health");
	descriptionuniquestring.push_back("below 30%, gain a shield that absorbs");
	descriptionuniquestring.push_back("up to 240 - 600 damage for 2 seconds.");
	descriptionuniquestring.push_back("(90 second cooldown)");
	childrenitems.push_back("Dagger"); childrenitems.push_back("Brawlers_Gloves"); childrenitems.push_back("Zeal");
	ATKSPEED = 30;
	CRIT = 25;
	MOVESPEED = 5;
	UNIQUEPASSIVEPD = true;
	COST = 2600;
	SELLCOST = 700;
}
void Item::BuildBrawlersGloves()
{
	ItemReset();
	extern SDL_Texture* ImageBrawlersGloves;
	image = ImageBrawlersGloves;
	name = "Brawlers_Gloves";
	descriptionstring.push_back("+10% Critical Strike Chance");
	buildsinto.push_back("Zeal"); buildsinto.push_back("Phantom_Dancer");
	CRIT = 10;
	COST = 400;
	SELLCOST = 400;
}
void Item::BuildDagger()
{
	ItemReset();
	extern SDL_Texture* ImageDagger;
	image = ImageDagger;
	name = "Dagger";
	descriptionstring.push_back("+12% Attack Speed");
	buildsinto.push_back("Zeal"); buildsinto.push_back("Phantom_Dancer");
	ATKSPEED = 12;
	COST = 300;
	SELLCOST = 300;
}
void Item::BuildZeal()
{
	ItemReset();
	extern SDL_Texture* ImageZeal;
	image = ImageZeal;
	name = "Zeal";
	descriptionstring.push_back("+15% Attack Speed");
	descriptionstring.push_back("+15% Critical Strike Chance");
	descriptionstring.push_back("+5 Movement Speed");
	buildsinto.push_back("Phantom_Dancer");
	childrenitems.push_back("Dagger"); childrenitems.push_back("Brawlers_Gloves");
	ATKSPEED = 15;
	CRIT = 15;
	MOVESPEED = 5;
	COST = 1200;
	SELLCOST = 500;
}
void Item::BuildSpiritVisage()
{
	ItemReset();
	extern SDL_Texture* ImageSpiritVisage;
	image = ImageSpiritVisage;
	name = "Spirit_Visage";
	descriptionstring.push_back("+450 Health");
	descriptionstring.push_back("+55 Magic Resist");
	descriptionstring.push_back("+100% Base Health Regen");
	descriptionstring.push_back("+10% Cooldown Reduction");
	childrenitems.push_back("Spectres_Cowl"); childrenitems.push_back("Kindlegem");
	HEALTH = 450;
	MR = 55;
	HEALTHREGEN = 100;
	CDR = 10;
	COST = 2800;
	SELLCOST = 800;
}
void Item::BuildSpectresCowl()
{
	ItemReset();
	extern SDL_Texture* ImageSpectresCowl;
	image = ImageSpectresCowl;
	name = "Spectres_Cowl";
	descriptionstring.push_back("+250 Health");
	descriptionstring.push_back("+25 Magic Resist");
	buildsinto.push_back("Spirit_Visage");
	childrenitems.push_back("Ruby_Crystal"); childrenitems.push_back("Null_Magic_Mantle");
	HEALTH = 250;
	MR = 25;
	COST = 1200;
	SELLCOST = 350;
}
void Item::BuildKindleGem()
{
	ItemReset();
	extern SDL_Texture* ImageKindleGem;
	image = ImageKindleGem;
	name = "Kindlegem";
	descriptionstring.push_back("+200 Health");
	descriptionstring.push_back("+10% Cooldown Reductiona");
	buildsinto.push_back("Spirit_Visage");
	childrenitems.push_back("Ruby_Crystal");
	HEALTH = 200;
	CDR = 10;
	COST = 800;
	SELLCOST = 400;
}
void Item::BuildNullMantle()
{
	ItemReset();
	extern SDL_Texture* ImageNullMantle;
	image = ImageNullMantle;
	name = "Null_Magic_Mantle";
	descriptionstring.push_back("+25 Magic Resist");
	buildsinto.push_back("Spectres_Cowl");
	MR = 25;
	COST = 450;
	SELLCOST = 450;
}
void Item::BuildRanduins()
{
	ItemReset();
	extern SDL_Texture* ImageRanduins;
	image = ImageRanduins;
	name = "Randuins_Omen";
	descriptionstring.push_back("+400 Health");
	descriptionstring.push_back("+60 Armor");
	descriptionuniquestring.push_back("UNIQUE PASSIVE - Randuins Omen");
	childrenitems.push_back("Giants_Belt"); childrenitems.push_back("Wardens_Mail");
	HEALTH = 400;
	ARMOR = 60;
	UNIQUEPASSIVERO = true;
	COST = 2900;
	SELLCOST = 900;
}
void Item::BuildGiantsBelt()
{
	ItemReset();
	extern SDL_Texture* ImageGiantsBelt;
	image = ImageGiantsBelt;
	name = "Giants_Belt";
	descriptionstring.push_back("+380 Health");
	buildsinto.push_back("Randuins_Omen"); buildsinto.push_back("Warmogs_Armor");
	childrenitems.push_back("Ruby_Crystal");
	HEALTH = 380;
	COST = 1000;
	SELLCOST = 600;
}
void Item::BuildClothArmor()
{
	ItemReset();
	extern SDL_Texture* ImageClothArmor;
	image = ImageClothArmor;
	name = "Cloth_Armor";
	descriptionstring.push_back("+15 Armor");
	buildsinto.push_back("Wardens_Mail");
	ARMOR = 15;
	COST = 300;
	SELLCOST = 300;
}
void Item::BuildWardensMail()
{
	ItemReset();
	extern SDL_Texture* ImageWardensMail;
	image = ImageWardensMail;
	name = "Wardens_Mail";
	descriptionstring.push_back("+40 Armor");
	buildsinto.push_back("Randuins_Omen");
	childrenitems.push_back("Cloth_Armor"); childrenitems.push_back("Cloth_Armor");
	ARMOR = 40;
	COST = 1000;
	SELLCOST = 400;
}
void Item::BuildWarmogs()
{
	ItemReset();
	extern SDL_Texture* ImageWarmogs;
	image = ImageWarmogs;
	name = "Warmogs_Armor";
	descriptionstring.push_back("+800 Health");
	descriptionstring.push_back("+200% Base Health Regen");
	descriptionstring.push_back("+10% Cooldown Reduction");
	descriptionuniquestring.push_back("UNIQUE PASSIVE - Gain large cheese");
	descriptionuniquestring.push_back("pizza during combat.");
	childrenitems.push_back("Giants_Belt"); childrenitems.push_back("Kindlegem"); childrenitems.push_back("Crystalline_Bracer");
	HEALTH = 800;
	HEALTHREGEN = 200;
	CDR = 10;
	UNIQUEPASSIVEWA = true;
	COST = 2850;
	SELLCOST = 400;
}
void Item::BuildCrystallineBracer()
{
	ItemReset();
	extern SDL_Texture* ImageCrystallineBracer;
	image = ImageCrystallineBracer;
	name = "Crystalline_Bracer";
	buildsinto.push_back("Warmogs_Armor");
	descriptionstring.push_back("+200 Health");
	descriptionstring.push_back("+50% Base Health Regen");
	childrenitems.push_back("Ruby_Crystal"); childrenitems.push_back("Rejuvination_Bead");
	HEALTH = 200;
	HEALTHREGEN = 50;
	COST = 650;
	SELLCOST = 100;
}
void Item::BuildRejuveBeads()
{
	ItemReset();
	extern SDL_Texture* ImageRejuveBeads;
	image = ImageRejuveBeads;
	name = "Rejuvination_Bead";
	descriptionstring.push_back("+50% Base Health Regen");
	buildsinto.push_back("Crystalline_Bracer");
	HEALTHREGEN = 50;
	COST = 150;
	SELLCOST = 150;
}
void Item::BuildBoots()
{
	ItemReset();
	extern SDL_Texture* ImageBoots;
	image = ImageBoots;
	name = "Boots_of_Speed";
	descriptionstring.push_back("+25 Movement Speed");
	MOVESPEED = 25;
	COST = 300;
	SELLCOST = 300;
}