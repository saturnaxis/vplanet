/**
   @file poise.c

   @brief Subroutines that control the energy balance model for climate

   @author Russell Deitrick ([deitrr](https://github.com/deitrr/))

   @date Sep 10 2015

*/

#include "vplanet.h"

void BodyCopyPoise(BODY *dest,BODY *src,int iTideModel,int iNumBodies,int iBody) {
    dest[iBody].bReadOrbitOblData = src[iBody].bReadOrbitOblData;
}

void InitializeUpdateTmpBodyPoise(BODY *body,CONTROL *control,UPDATE *update,int iBody) {
    
    if (body[iBody].bReadOrbitOblData) {
    int iLine;

    control->Evolve.tmpBody[iBody].daSemiSeries = malloc(body[iBody].iNLines*sizeof(double));
    control->Evolve.tmpBody[iBody].daHeccSeries = malloc(body[iBody].iNLines*sizeof(double));
    control->Evolve.tmpBody[iBody].daKeccSeries = malloc(body[iBody].iNLines*sizeof(double));


    for (iLine=0;iLine<body[iBody].iNLines;iLine++) {
      control->Evolve.tmpBody[iBody].daSemiSeries[iLine] = body[iBody].daSemiSeries[iLine];
      control->Evolve.tmpBody[iBody].daHeccSeries[iLine] = body[iBody].daHeccSeries[iLine];
      control->Evolve.tmpBody[iBody].daKeccSeries[iLine] = body[iBody].daKeccSeries[iLine];
    }
  } 
  
}

/**************** POISE options ********************/

void ReadLatCellNum(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,iTmp;
  AddOptionInt(files->Infile[iFile].cIn,options->cName,&iTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].iNumLats = iTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].iNumLats,files->iNumInputs);
}

void ReadOrbitOblData(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,bTmp;
  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].bReadOrbitOblData = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    body[iFile-1].bReadOrbitOblData = options->dDefault;
}

void ReadFileOrbitOblData(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1;
  char cTmp[OPTLEN];

  AddOptionString(files->Infile[iFile].cIn,options->cName,cTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    /* Cannot exist in primary input file -- Each body has an output file */
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    strcpy(body[iFile-1].cFileOrbitOblData,cTmp);
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
//       sprintf(body[iFile-1].cFileOrbitData,"%s",options[OPT_FILEORBITDATA].cDefault);
      strcpy(body[iFile-1].cFileOrbitOblData,options->cDefault);
}

void ReadPlanckA(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dPlanckA = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dPlanckA = options->dDefault;
}

void ReadPlanckB(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dPlanckB = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dPlanckB = options->dDefault;
}

void ReadSurfAlbedo(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dSurfAlbedo = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dSurfAlbedo = options->dDefault;
}

void ReadIceAlbedo(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dIceAlbedo = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dIceAlbedo = options->dDefault;
}

void ReadTGlobalInit(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dTGlobalInit = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dTGlobalInit = options->dDefault;
}

void ReadPCO2(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dpCO2 = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dpCO2 = options->dDefault;
}

void ReadDiffusion(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dDiffCoeff = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dDiffCoeff = options->dDefault;
}

void ReadFixIceLat(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dFixIceLat = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dFixIceLat = options->dDefault;
}

void ReadHeatCapAnn(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dHeatCapAnn = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dHeatCapAnn = options->dDefault;
}


void ReadIceDepRate(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dIceDepRate = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dIceDepRate = options->dDefault;
}

void ReadHadley(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,bTmp;
  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].bHadley = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].bHadley,files->iNumInputs);
}

void ReadCalcAB(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,bTmp;
  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].bCalcAB = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].bCalcAB,files->iNumInputs);
}

void ReadColdStart(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,bTmp;
  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].bColdStart = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].bColdStart,files->iNumInputs);
}

void ReadAlbedoZA(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,bTmp;
  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].bAlbedoZA = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].bAlbedoZA,files->iNumInputs);
}


void ReadSeaIceModel(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bSeaIceModel = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].bSeaIceModel,files->iNumInputs);
}

void ReadMEPDiff(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bMEPDiff = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].bMEPDiff,files->iNumInputs);
}

void ReadIceSheets(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bIceSheets = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else {
    AssignDefaultInt(options,&body[iFile-1].bIceSheets,files->iNumInputs);
  }
}

void ReadSkipSeasEnabled(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bSkipSeasEnabled = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else {
    AssignDefaultInt(options,&body[iFile-1].bSkipSeasEnabled,files->iNumInputs);
  }
}

void ReadAccuracyMode(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bAccuracyMode = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else {
    AssignDefaultInt(options,&body[iFile-1].bAccuracyMode,files->iNumInputs);
  }
}

void ReadElevFB(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bElevFB = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else {
    AssignDefaultInt(options,&body[iFile-1].bElevFB,files->iNumInputs);
  }
}

void ReadForceObliq(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bForceObliq = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else {
    AssignDefaultInt(options,&body[iFile-1].bForceObliq,files->iNumInputs);
  }
}

void ReadForceEcc(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bForceEcc = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else {
    AssignDefaultInt(options,&body[iFile-1].bForceEcc,files->iNumInputs);
  }
}

void ReadDiffRot(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1, bTmp;

  AddOptionBool(files->Infile[iFile].cIn,options->cName,&bTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].bDiffRot = bTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else {
    AssignDefaultInt(options,&body[iFile-1].bDiffRot,files->iNumInputs);
  }
}

void ReadClimateModel(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter can exist in any file, but only once */
  int lTmp=-1;
  char cTmp[OPTLEN];

  /* Climate Model, use #defined variables */

  AddOptionString(files->Infile[iFile].cIn,options->cName,cTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    /* This parameter can not appear in the primary input,
       as it is module specific (it's easier to code this
       way. It should also only appear in one body file
       so as different tidal models cannot be called. */
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    //CheckDuplication(files,options,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    if (!memcmp(sLower(cTmp),"ann",3)) {
      body[iFile-1].bClimateModel = ANN;
    } else if (!memcmp(sLower(cTmp),"sea",3)) {
      body[iFile-1].bClimateModel = SEA;
    } else {
      if (control->Io.iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Unknown argument to %s: %s. Options are ann or sea.\n",options->cName,cTmp);
      LineExit(files->Infile[iFile].cIn,lTmp);
    }
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].bClimateModel,files->iNumInputs);
}

void ReadOLRModel(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter can exist in any file, but only once */
  int lTmp=-1;
  char cTmp[OPTLEN];

  /* OLR model, use #defined variables (used with CalcAB = 1)*/

  AddOptionString(files->Infile[iFile].cIn,options->cName,cTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    //CheckDuplication(files,options,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    if (!memcmp(sLower(cTmp),"wk97",3)) {
      body[iFile-1].iOLRModel = WK97;
    } else if (!memcmp(sLower(cTmp),"hm16",3)) {
      body[iFile-1].iOLRModel = HM16;
    } else if (!memcmp(sLower(cTmp),"sms09",3)) {
      body[iFile-1].iOLRModel = SMS09;
    } else {
      if (control->Io.iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Unknown argument to %s: %s. Options are wk97 or hm16.\n",options->cName,cTmp);
      LineExit(files->Infile[iFile].cIn,lTmp);
    }
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].iOLRModel,files->iNumInputs);
}

void ReadGeography(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter can exist in any file, but only once */
  int lTmp=-1;
  char cTmp[OPTLEN];

  /* Albedo type, use #defined variables */

  AddOptionString(files->Infile[iFile].cIn,options->cName,cTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    /* This parameter can not appear in the primary input,
       as it is module specific (it's easier to code this
       way. It should also only appear in one body file
       so as different tidal models cannot be called. */
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    //CheckDuplication(files,options,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    if (!memcmp(sLower(cTmp),"uni3",4)) {
      body[iFile-1].iGeography = UNIFORM3;
    } else if (!memcmp(sLower(cTmp),"modn",4)) {
      body[iFile-1].iGeography = MODERN;
    } else {
      if (control->Io.iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Unknown argument to %s: %s. Options are uni3 or modn.\n",options->cName,cTmp);
      LineExit(files->Infile[iFile].cIn,lTmp);
    }
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else {
    body[iFile-1].iGeography = options->dDefault;
  }
}


void ReadInitIceLat(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dInitIceLat = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dInitIceLat = options->dDefault;
}

void ReadInitIceHeight(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dInitIceHeight = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dInitIceHeight = options->dDefault;
}

void ReadHeatCapLand(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dHeatCapLand = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dHeatCapLand = options->dDefault;
}

void ReadSeaIceConduct(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dSeaIceConduct = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dSeaIceConduct = options->dDefault;
}

void ReadHeatCapWater(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dHeatCapWater = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dHeatCapWater = options->dDefault;
}

void ReadAlbedoLand(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dAlbedoLand = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dAlbedoLand = options->dDefault;
}

void ReadSeasOutputTime(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dSeasOutputTime = dTmp*fdUnitsTime(control->Units[iFile].iTime);;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dSeasOutputTime = options->dDefault;
}

void ReadAlbedoWater(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dAlbedoWater = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dAlbedoWater = options->dDefault;
}

void ReadObliqAmp(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dObliqAmp = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dObliqAmp = options->dDefault;
}

void ReadObliqPer(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dObliqPer = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dObliqPer = options->dDefault;
}

void ReadEccAmp(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dEccAmp = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dEccAmp = options->dDefault;
}

void ReadEccPer(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dEccPer = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dEccPer = options->dDefault;
}

void ReadMixingDepth(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dMixingDepth = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dMixingDepth = options->dDefault;
}

void ReadFrzTSeaIce(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dFrzTSeaIce = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dFrzTSeaIce = options->dDefault;
}

void ReadNuLandWater(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dNuLandWater = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dNuLandWater = options->dDefault;
}

void ReadLapseR(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dLapseR = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dLapseR = options->dDefault;
}

void ReadRefHeight(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dRefHeight = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dRefHeight = options->dDefault;
}

void ReadSpinUpTol(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dSpinUpTol = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dSpinUpTol = options->dDefault;
}

void ReadAblateFF(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  /* This parameter cannot exist in primary file */
  int lTmp=-1;
  double dTmp;

  AddOptionDouble(files->Infile[iFile].cIn,options->cName,&dTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    body[iFile-1].dAblateFF = dTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    if (iFile > 0)
      body[iFile-1].dAblateFF = options->dDefault;
}

void ReadNStepInYear(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,iTmp;
  AddOptionInt(files->Infile[iFile].cIn,options->cName,&iTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].iNStepInYear = iTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].iNStepInYear,files->iNumInputs);
}

void ReadNumYears(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,iTmp;
  AddOptionInt(files->Infile[iFile].cIn,options->cName,&iTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].iNumYears = iTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].iNumYears,files->iNumInputs);
}

void ReadIceDt(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,iTmp;
  AddOptionInt(files->Infile[iFile].cIn,options->cName,&iTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].iIceTimeStep = iTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].iIceTimeStep,files->iNumInputs);
}

void ReadReRunSeas(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,int iFile) {
  int lTmp=-1,iTmp;
  AddOptionInt(files->Infile[iFile].cIn,options->cName,&iTmp,&lTmp,control->Io.iVerbose);
  if (lTmp >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp,control->Io.iVerbose);
    /* Option was found */
    body[iFile-1].iReRunSeas = iTmp;
    UpdateFoundOption(&files->Infile[iFile],options,lTmp,iFile);
  } else
    AssignDefaultInt(options,&body[iFile-1].iReRunSeas,files->iNumInputs);
}

void InitializeOptionsPoise(OPTIONS *options,fnReadOption fnRead[]) {
  sprintf(options[OPT_LATCELLNUM].cName,"iLatCellNum");
  sprintf(options[OPT_LATCELLNUM].cDescr,"Number of latitude cells used in climate model");
  sprintf(options[OPT_LATCELLNUM].cDefault,"50");
  options[OPT_LATCELLNUM].dDefault = 50;
  options[OPT_LATCELLNUM].iType = 1;
  options[OPT_LATCELLNUM].iMultiFile = 1;
  fnRead[OPT_LATCELLNUM] = &ReadLatCellNum;
  
  sprintf(options[OPT_READORBITOBLDATA].cName,"bReadOrbitOblData");
  sprintf(options[OPT_READORBITOBLDATA].cDescr,"Read in orbital data and use with distrot");
  sprintf(options[OPT_READORBITOBLDATA].cDefault,"0");
  options[OPT_READORBITOBLDATA].dDefault = 0;
  options[OPT_READORBITOBLDATA].iType = 0;
  options[OPT_READORBITOBLDATA].iMultiFile = 1;
  fnRead[OPT_READORBITOBLDATA] = &ReadOrbitOblData;

  sprintf(options[OPT_FILEORBITOBLDATA].cName,"sFileOrbitOblData");
  sprintf(options[OPT_FILEORBITOBLDATA].cDescr,"Name of file containing orbit time series");
  sprintf(options[OPT_FILEORBITOBLDATA].cDefault,"Obl_data.txt");
  options[OPT_FILEORBITOBLDATA].iType = 3;
  fnRead[OPT_FILEORBITOBLDATA] = &ReadFileOrbitOblData;

  sprintf(options[OPT_PLANCKA].cName,"dPlanckA");
  sprintf(options[OPT_PLANCKA].cDescr,"Constant 'A' used in OLR calculation");
  sprintf(options[OPT_PLANCKA].cDefault,"203.3");
  options[OPT_PLANCKA].dDefault = 203.3;
  options[OPT_PLANCKA].iType = 2;
  options[OPT_PLANCKA].iMultiFile = 1;
  fnRead[OPT_PLANCKA] = &ReadPlanckA;

  sprintf(options[OPT_PLANCKB].cName,"dPlanckB");
  sprintf(options[OPT_PLANCKB].cDescr,"Sensitivity 'B' used in OLR calculation");
  sprintf(options[OPT_PLANCKB].cDefault,"2.09");
  options[OPT_PLANCKB].dDefault = 2.09;
  options[OPT_PLANCKB].iType = 2;
  options[OPT_PLANCKB].iMultiFile = 1;
  fnRead[OPT_PLANCKB] = &ReadPlanckB;

  sprintf(options[OPT_ICEALBEDO].cName,"dIceAlbedo");
  sprintf(options[OPT_ICEALBEDO].cDescr,"Albedo of ice");
  sprintf(options[OPT_ICEALBEDO].cDefault,"0.6");
  options[OPT_ICEALBEDO].dDefault = 0.6;
  options[OPT_ICEALBEDO].iType = 2;
  options[OPT_ICEALBEDO].iMultiFile = 1;
  fnRead[OPT_ICEALBEDO] = &ReadIceAlbedo;

  sprintf(options[OPT_SURFALBEDO].cName,"dSurfAlbedo");
  sprintf(options[OPT_SURFALBEDO].cDescr,"Albedo of (ice-free) surface");
  sprintf(options[OPT_SURFALBEDO].cDefault,"0.3");
  options[OPT_SURFALBEDO].dDefault = 0.3;
  options[OPT_SURFALBEDO].iType = 2;
  options[OPT_SURFALBEDO].iMultiFile = 1;
  fnRead[OPT_SURFALBEDO] = &ReadSurfAlbedo;

  sprintf(options[OPT_TGLOBALEST].cName,"dTGlobalInit");
  sprintf(options[OPT_TGLOBALEST].cDescr,"Estimate of initial global temperature");
  sprintf(options[OPT_TGLOBALEST].cDefault,"14.85");
  options[OPT_TGLOBALEST].dDefault = 14.85;
  options[OPT_TGLOBALEST].iType = 2;
  options[OPT_TGLOBALEST].iMultiFile = 1;
  fnRead[OPT_TGLOBALEST] = &ReadTGlobalInit;

  sprintf(options[OPT_PCO2].cName,"dpCO2");
  sprintf(options[OPT_PCO2].cDescr,"Partial pressure of CO2 in atmosphere");
  sprintf(options[OPT_PCO2].cDefault,"3.3e-4");
  options[OPT_PCO2].dDefault = 3.3e-4;
  options[OPT_PCO2].iType = 2;
  options[OPT_PCO2].iMultiFile = 1;
  fnRead[OPT_PCO2] = &ReadPCO2;

  sprintf(options[OPT_CALCAB].cName,"bCalcAB");
  sprintf(options[OPT_CALCAB].cDescr,"Calculate A and B in OLR function, from (T & pCO2)");
  sprintf(options[OPT_CALCAB].cDefault,"0");
  options[OPT_CALCAB].dDefault = 0;
  options[OPT_CALCAB].iType = 0;
  options[OPT_CALCAB].iMultiFile = 1;
  fnRead[OPT_CALCAB] = &ReadCalcAB;

  sprintf(options[OPT_DIFFUSION].cName,"dDiffusion");
  sprintf(options[OPT_DIFFUSION].cDescr,"Heat diffusion coefficient");
  sprintf(options[OPT_DIFFUSION].cDefault,"0.44");
  options[OPT_DIFFUSION].dDefault = 0.44;
  options[OPT_DIFFUSION].iType = 2;
  options[OPT_DIFFUSION].iMultiFile = 1;
  fnRead[OPT_DIFFUSION] = &ReadDiffusion;

  sprintf(options[OPT_HADLEY].cName,"bHadley");
  sprintf(options[OPT_HADLEY].cDescr,"Enable Hadley circulation");
  sprintf(options[OPT_HADLEY].cDefault,"0");
  options[OPT_HADLEY].dDefault = 0;
  options[OPT_HADLEY].iType = 0;
  options[OPT_HADLEY].iMultiFile = 1;
  fnRead[OPT_HADLEY] = &ReadHadley;

  sprintf(options[OPT_COLDSTART].cName,"bColdStart");
  sprintf(options[OPT_COLDSTART].cDescr,"Start from snowball Earth conditions");
  sprintf(options[OPT_COLDSTART].cDefault,"0");
  options[OPT_COLDSTART].dDefault = 0;
  options[OPT_COLDSTART].iType = 0;
  options[OPT_COLDSTART].iMultiFile = 1;
  fnRead[OPT_COLDSTART] = &ReadColdStart;

  sprintf(options[OPT_FIXICELAT].cName,"dFixIceLat");
  sprintf(options[OPT_FIXICELAT].cDescr,"Fixes ice line latitude to a set value");
  sprintf(options[OPT_FIXICELAT].cDefault,"None");
  options[OPT_FIXICELAT].dDefault = 0;
  options[OPT_FIXICELAT].iType = 2;
  options[OPT_FIXICELAT].iMultiFile = 1;
  fnRead[OPT_FIXICELAT] = &ReadFixIceLat;

  sprintf(options[OPT_ALBEDOZA].cName,"bAlbedoZA");
  sprintf(options[OPT_ALBEDOZA].cDescr,"Use albedo based on zenith angle");
  sprintf(options[OPT_ALBEDOZA].cDefault,"0");
  options[OPT_ALBEDOZA].dDefault = 0;
  options[OPT_ALBEDOZA].iType = 0;
  options[OPT_ALBEDOZA].iMultiFile = 1;
  fnRead[OPT_ALBEDOZA] = &ReadAlbedoZA;

  sprintf(options[OPT_MEPDIFF].cName,"bMEPDiff");
  sprintf(options[OPT_MEPDIFF].cDescr,"Calculate diffusion from max entropy production (D=B/4)");
  sprintf(options[OPT_MEPDIFF].cDefault,"0");
  options[OPT_MEPDIFF].dDefault = 0;
  options[OPT_MEPDIFF].iType = 0;
  options[OPT_MEPDIFF].iMultiFile = 1;
  fnRead[OPT_MEPDIFF] = &ReadMEPDiff;

  sprintf(options[OPT_HEATCAPANN].cName,"dHeatCapAnn");
  sprintf(options[OPT_HEATCAPANN].cDescr,"Surface heat capacity in annual model");
  sprintf(options[OPT_HEATCAPANN].cDefault,"0.2");
  options[OPT_HEATCAPANN].dDefault = 0.2;
  options[OPT_HEATCAPANN].iType = 2;
  options[OPT_HEATCAPANN].iMultiFile = 1;
  fnRead[OPT_HEATCAPANN] = &ReadHeatCapAnn;

  sprintf(options[OPT_ICEDEPRATE].cName,"dIceDepRate");
  sprintf(options[OPT_ICEDEPRATE].cDescr,"Deposition rate of ice/snow to form ice sheets");
  sprintf(options[OPT_ICEDEPRATE].cDefault,"2.9e-5");
  options[OPT_ICEDEPRATE].dDefault = 2.9e-5;
  options[OPT_ICEDEPRATE].iType = 2;
  options[OPT_ICEDEPRATE].iMultiFile = 1;
  fnRead[OPT_ICEDEPRATE] = &ReadIceDepRate;

  sprintf(options[OPT_ICESHEETS].cName,"bIceSheets");
  sprintf(options[OPT_ICESHEETS].cDescr,"Include ice sheets");
  sprintf(options[OPT_ICESHEETS].cDefault,"0");
  options[OPT_ICESHEETS].dDefault = 0;
  options[OPT_ICESHEETS].iType = 0;
  options[OPT_ICESHEETS].iMultiFile = 1;
  fnRead[OPT_ICESHEETS] = &ReadIceSheets;

  sprintf(options[OPT_INITICELAT].cName,"dInitIceLat");
  sprintf(options[OPT_INITICELAT].cDescr,"Sets initial ice sheet latitude");
  sprintf(options[OPT_INITICELAT].cDefault,"90");
  options[OPT_INITICELAT].dDefault = 90.0;
  options[OPT_INITICELAT].iType = 2;
  options[OPT_INITICELAT].iMultiFile = 1;
  fnRead[OPT_INITICELAT] = &ReadInitIceLat;

  sprintf(options[OPT_INITICEHEIGHT].cName,"dInitIceHeight");
  sprintf(options[OPT_INITICEHEIGHT].cDescr,"Sets initial ice sheet height");
  sprintf(options[OPT_INITICEHEIGHT].cDefault,"50");
  options[OPT_INITICEHEIGHT].dDefault = 50.0;
  options[OPT_INITICEHEIGHT].iType = 2;
  options[OPT_INITICEHEIGHT].iMultiFile = 1;
  fnRead[OPT_INITICEHEIGHT] = &ReadInitIceHeight;

  sprintf(options[OPT_CLIMATEMODEL].cName,"bClimateModel");
  sprintf(options[OPT_CLIMATEMODEL].cDescr,"Use annual or seasonal model");
  sprintf(options[OPT_CLIMATEMODEL].cDefault,"ann");
  options[OPT_CLIMATEMODEL].dDefault = ANN;
  options[OPT_CLIMATEMODEL].iType = 1;
  options[OPT_CLIMATEMODEL].iMultiFile = 1;
  fnRead[OPT_CLIMATEMODEL] = &ReadClimateModel;

  sprintf(options[OPT_OLRMODEL].cName,"iOLRModel");
  sprintf(options[OPT_OLRMODEL].cDescr,"Outgoing longwave rad model");
  sprintf(options[OPT_OLRMODEL].cDefault,"sms09");
  options[OPT_OLRMODEL].dDefault = SMS09;
  options[OPT_OLRMODEL].iType = 1;
  options[OPT_OLRMODEL].iMultiFile = 1;
  fnRead[OPT_OLRMODEL] = &ReadOLRModel;

  sprintf(options[OPT_SKIPSEASENABLED].cName,"bSkipSeasEnabled");
  sprintf(options[OPT_SKIPSEASENABLED].cDescr,"Run annual before seasonal and allow skip seas");
  sprintf(options[OPT_SKIPSEASENABLED].cDefault,"0");
  options[OPT_SKIPSEASENABLED].dDefault = 0;
  options[OPT_SKIPSEASENABLED].iType = 0;
  options[OPT_SKIPSEASENABLED].iMultiFile = 1;
  fnRead[OPT_SKIPSEASENABLED] = &ReadSkipSeasEnabled;

  sprintf(options[OPT_HEATCAPLAND].cName,"dHeatCapLand");
  sprintf(options[OPT_HEATCAPLAND].cDescr,"Land heat capacity in seasonal model");
  sprintf(options[OPT_HEATCAPLAND].cDefault,"1.42e7");
  options[OPT_HEATCAPLAND].dDefault = 1.42e7;
  options[OPT_HEATCAPLAND].iType = 2;
  options[OPT_HEATCAPLAND].iMultiFile = 1;
  fnRead[OPT_HEATCAPLAND] = &ReadHeatCapLand;

  sprintf(options[OPT_HEATCAPWATER].cName,"dHeatCapWater");
  sprintf(options[OPT_HEATCAPWATER].cDescr,"Water heat capacity per meter in seasonal model");
  sprintf(options[OPT_HEATCAPWATER].cDefault,"4.2e6");
  options[OPT_HEATCAPWATER].dDefault = 4.2e6;
  options[OPT_HEATCAPWATER].iType = 2;
  options[OPT_HEATCAPWATER].iMultiFile = 1;
  fnRead[OPT_HEATCAPWATER] = &ReadHeatCapWater;

  sprintf(options[OPT_MIXINGDEPTH].cName,"dMixingDepth");
  sprintf(options[OPT_MIXINGDEPTH].cDescr,"Mixing depth of ocean in seasonal model");
  sprintf(options[OPT_MIXINGDEPTH].cDefault,"70");
  options[OPT_MIXINGDEPTH].dDefault = 70.;
  options[OPT_MIXINGDEPTH].iType = 2;
  options[OPT_MIXINGDEPTH].iMultiFile = 1;
  fnRead[OPT_MIXINGDEPTH] = &ReadMixingDepth;

  sprintf(options[OPT_FRZTSEAICE].cName,"dFrzTSeaIce");
  sprintf(options[OPT_FRZTSEAICE].cDescr,"Temp of sea ice formation in seasonal model");
  sprintf(options[OPT_FRZTSEAICE].cDefault,"-2");
  options[OPT_FRZTSEAICE].dDefault = -2.;
  options[OPT_FRZTSEAICE].iType = 2;
  options[OPT_FRZTSEAICE].iMultiFile = 1;
  fnRead[OPT_FRZTSEAICE] = &ReadFrzTSeaIce;

  sprintf(options[OPT_NULANDWATER].cName,"dNuLandWater");
  sprintf(options[OPT_NULANDWATER].cDescr,"Coefficient of land-ocean heat flux");
  sprintf(options[OPT_NULANDWATER].cDefault,"0.81");
  options[OPT_NULANDWATER].dDefault = 0.81;
  options[OPT_NULANDWATER].iType = 2;
  options[OPT_NULANDWATER].iMultiFile = 1;
  fnRead[OPT_NULANDWATER] = &ReadNuLandWater;

  sprintf(options[OPT_NSTEPINYEAR].cName,"iNStepInYear");
  sprintf(options[OPT_NSTEPINYEAR].cDescr,"Number of time-steps/year in seasonal model");
  sprintf(options[OPT_NSTEPINYEAR].cDefault,"60");
  options[OPT_NSTEPINYEAR].dDefault = 60;
  options[OPT_NSTEPINYEAR].iType = 1;
  options[OPT_NSTEPINYEAR].iMultiFile = 1;
  fnRead[OPT_NSTEPINYEAR] = &ReadNStepInYear;

  sprintf(options[OPT_NUMYEARS].cName,"iNumYears");
  sprintf(options[OPT_NUMYEARS].cDescr,"Number of years to run seasonal model");
  sprintf(options[OPT_NUMYEARS].cDefault,"10");
  options[OPT_NUMYEARS].dDefault = 10;
  options[OPT_NUMYEARS].iType = 1;
  options[OPT_NUMYEARS].iMultiFile = 1;
  fnRead[OPT_NUMYEARS] = &ReadNumYears;

  sprintf(options[OPT_SEAICEMODEL].cName,"bSeaIceModel");
  sprintf(options[OPT_SEAICEMODEL].cDescr,"model sea ice dynamics and heat flow?");
  sprintf(options[OPT_SEAICEMODEL].cDefault,"1");
  options[OPT_SEAICEMODEL].dDefault = 1;
  options[OPT_SEAICEMODEL].iType = 0;
  options[OPT_SEAICEMODEL].iMultiFile = 1;
  fnRead[OPT_SEAICEMODEL] = &ReadSeaIceModel;

  sprintf(options[OPT_ICECONDUCT].cName,"dSeaIceConduct");
  sprintf(options[OPT_ICECONDUCT].cDescr,"Heat conductivity of sea ice");
  sprintf(options[OPT_ICECONDUCT].cDefault,"2");
  options[OPT_ICECONDUCT].dDefault = 2.;
  options[OPT_ICECONDUCT].iType = 2;
  options[OPT_ICECONDUCT].iMultiFile = 1;
  fnRead[OPT_ICECONDUCT] = &ReadSeaIceConduct;

  sprintf(options[OPT_ALBEDOLAND].cName,"dAlbedoLand");
  sprintf(options[OPT_ALBEDOLAND].cDescr,"albedo of dry land");
  sprintf(options[OPT_ALBEDOLAND].cDefault,"0.363");
  options[OPT_ALBEDOLAND].dDefault = 0.363;
  options[OPT_ALBEDOLAND].iType = 2;
  options[OPT_ALBEDOLAND].iMultiFile = 1;
  fnRead[OPT_ALBEDOLAND] = &ReadAlbedoLand;

  sprintf(options[OPT_ALBEDOWATER].cName,"dAlbedoWater");
  sprintf(options[OPT_ALBEDOWATER].cDescr,"albedo of open water");
  sprintf(options[OPT_ALBEDOWATER].cDefault,"0.263");
  options[OPT_ALBEDOWATER].dDefault = 0.263;
  options[OPT_ALBEDOWATER].iType = 2;
  options[OPT_ALBEDOWATER].iMultiFile = 1;
  fnRead[OPT_ALBEDOWATER] = &ReadAlbedoWater;

  sprintf(options[OPT_ICEDT].cName,"iIceDt");
  sprintf(options[OPT_ICEDT].cDescr,"Minimum ice sheet timestep (unit orbital period)");
  sprintf(options[OPT_ICEDT].cDefault,"5");
  options[OPT_ICEDT].dDefault = 5;
  options[OPT_ICEDT].iType = 1;
  options[OPT_ICEDT].iMultiFile = 1;
  fnRead[OPT_ICEDT] = &ReadIceDt;

  sprintf(options[OPT_RERUNSEAS].cName,"iReRunSeas");
  sprintf(options[OPT_RERUNSEAS].cDescr,"how often to rerun seasonal in ice sheet model, in number of orbital periods");
  sprintf(options[OPT_RERUNSEAS].cDefault,"500");
  options[OPT_RERUNSEAS].dDefault = 5;
  options[OPT_RERUNSEAS].iType = 1;
  options[OPT_RERUNSEAS].iMultiFile = 1;
  fnRead[OPT_RERUNSEAS] = &ReadReRunSeas;

  sprintf(options[OPT_GEOGRAPHY].cName,"iGeography");
  sprintf(options[OPT_GEOGRAPHY].cDescr,"Type of land distribution");
  sprintf(options[OPT_GEOGRAPHY].cDefault,"uni3");
  options[OPT_GEOGRAPHY].dDefault = UNIFORM3;
  options[OPT_GEOGRAPHY].iType = 1;
  options[OPT_GEOGRAPHY].iMultiFile = 1;
  fnRead[OPT_GEOGRAPHY] = &ReadGeography;

  sprintf(options[OPT_SEASOUTPUTTIME].cName,"dSeasOutputTime");
  sprintf(options[OPT_SEASOUTPUTTIME].cDescr,"Output interval for seasonal parameters");
  sprintf(options[OPT_SEASOUTPUTTIME].cDefault,"0");
  options[OPT_SEASOUTPUTTIME].dDefault = 0;
  options[OPT_SEASOUTPUTTIME].iType = 2;
  options[OPT_SEASOUTPUTTIME].iMultiFile = 1;
  fnRead[OPT_SEASOUTPUTTIME] = &ReadSeasOutputTime;

  sprintf(options[OPT_FORCEOBLIQ].cName,"bForceObliq");
  sprintf(options[OPT_FORCEOBLIQ].cDescr,"Force obliquity to evolve sinusoidally");
  sprintf(options[OPT_FORCEOBLIQ].cDefault,"0");
  options[OPT_FORCEOBLIQ].dDefault = 0;
  options[OPT_FORCEOBLIQ].iType = 2;
  options[OPT_FORCEOBLIQ].iMultiFile = 1;
  fnRead[OPT_FORCEOBLIQ] = &ReadForceObliq;

  sprintf(options[OPT_DIFFROT].cName,"bDiffRot");
  sprintf(options[OPT_DIFFROT].cDescr,"Adjust heat diffusion for rotation rate");
  sprintf(options[OPT_DIFFROT].cDefault,"0");
  options[OPT_DIFFROT].dDefault = 0;
  options[OPT_DIFFROT].iType = 2;
  options[OPT_DIFFROT].iMultiFile = 1;
  fnRead[OPT_DIFFROT] = &ReadDiffRot;

  sprintf(options[OPT_OBLIQAMP].cName,"dObliqAmp");
  sprintf(options[OPT_OBLIQAMP].cDescr,"Amplitude of forced obliquity oscill");
  sprintf(options[OPT_OBLIQAMP].cDefault,"50");
  options[OPT_OBLIQAMP].dDefault = 50;
  options[OPT_OBLIQAMP].iType = 2;
  options[OPT_OBLIQAMP].iMultiFile = 1;
  fnRead[OPT_OBLIQAMP] = &ReadObliqAmp;

  sprintf(options[OPT_OBLIQPER].cName,"dObliqPer");
  sprintf(options[OPT_OBLIQPER].cDescr,"Period of forced obliquity oscill");
  sprintf(options[OPT_OBLIQPER].cDefault,"50000");
  options[OPT_OBLIQPER].dDefault = 50000;
  options[OPT_OBLIQPER].iType = 2;
  options[OPT_OBLIQPER].iMultiFile = 1;
  fnRead[OPT_OBLIQPER] = &ReadObliqPer;

  sprintf(options[OPT_FORCEECC].cName,"bForceEcc");
  sprintf(options[OPT_FORCEECC].cDescr,"Force Eccentricity to evolve sinusoidally");
  sprintf(options[OPT_FORCEECC].cDefault,"0");
  options[OPT_FORCEECC].dDefault = 0;
  options[OPT_FORCEECC].iType = 2;
  options[OPT_FORCEECC].iMultiFile = 1;
  fnRead[OPT_FORCEECC] = &ReadForceEcc;

  sprintf(options[OPT_ECCAMP].cName,"dEccAmp");
  sprintf(options[OPT_ECCAMP].cDescr,"Amplitude of forced eccentricity oscill");
  sprintf(options[OPT_ECCAMP].cDefault,"0.1");
  options[OPT_ECCAMP].dDefault = 0.1;
  options[OPT_ECCAMP].iType = 2;
  options[OPT_ECCAMP].iMultiFile = 1;
  fnRead[OPT_ECCAMP] = &ReadEccAmp;

  sprintf(options[OPT_ECCPER].cName,"dEccPer");
  sprintf(options[OPT_ECCPER].cDescr,"Period of forced eccentricity oscill");
  sprintf(options[OPT_ECCPER].cDefault,"50000");
  options[OPT_ECCPER].dDefault = 50000;
  options[OPT_ECCPER].iType = 2;
  options[OPT_ECCPER].iMultiFile = 1;
  fnRead[OPT_ECCPER] = &ReadEccPer;

  sprintf(options[OPT_ACCUMODE].cName,"bAccuracyMode");
  sprintf(options[OPT_ACCUMODE].cDescr,"Re-invert matrix every EBM time step");
  sprintf(options[OPT_ACCUMODE].cDefault,"0");
  options[OPT_ACCUMODE].dDefault = 0;
  options[OPT_ACCUMODE].iType = 2;
  options[OPT_ACCUMODE].iMultiFile = 1;
  fnRead[OPT_ACCUMODE] = &ReadAccuracyMode;

  sprintf(options[OPT_ELEVFB].cName,"bElevFB");
  sprintf(options[OPT_ELEVFB].cDescr,"Use elevation feedback for ice sheet ablation");
  sprintf(options[OPT_ELEVFB].cDefault,"0");
  options[OPT_ELEVFB].dDefault = 0;
  options[OPT_ELEVFB].iType = 2;
  options[OPT_ELEVFB].iMultiFile = 1;
  fnRead[OPT_ELEVFB] = &ReadElevFB;

  sprintf(options[OPT_LAPSER].cName,"dLapseR");
  sprintf(options[OPT_LAPSER].cDescr,"Dry adiabatic lapse rate (for elev feedback)");
  sprintf(options[OPT_LAPSER].cDefault,"9.8e-3 C/m");
  options[OPT_LAPSER].dDefault = 9.8e-3;
  options[OPT_LAPSER].iType = 2;
  options[OPT_LAPSER].iMultiFile = 1;
  fnRead[OPT_LAPSER] = &ReadLapseR;

  sprintf(options[OPT_REFHEIGHT].cName,"dRefHeight");
  sprintf(options[OPT_REFHEIGHT].cDescr,"Reference height of atmos temp (for elev feedback)");
  sprintf(options[OPT_REFHEIGHT].cDefault,"1000 m");
  options[OPT_REFHEIGHT].dDefault = 1000.0;
  options[OPT_REFHEIGHT].iType = 2;
  options[OPT_REFHEIGHT].iMultiFile = 1;
  fnRead[OPT_REFHEIGHT] = &ReadRefHeight;

  sprintf(options[OPT_ABLATEFF].cName,"dAblateFF");
  sprintf(options[OPT_ABLATEFF].cDescr,"Ice ablation fudge factor");
  sprintf(options[OPT_ABLATEFF].cDefault,"2.3");
  options[OPT_ABLATEFF].dDefault = 2.3;
  options[OPT_ABLATEFF].iType = 2;
  options[OPT_ABLATEFF].iMultiFile = 1;
  fnRead[OPT_ABLATEFF] = &ReadAblateFF;

  sprintf(options[OPT_SPINUPTOL].cName,"dSpinUpTol");
  sprintf(options[OPT_SPINUPTOL].cDescr,"Tolerance for spin up phase");
  sprintf(options[OPT_SPINUPTOL].cDefault,"0.1 deg C");
  options[OPT_SPINUPTOL].dDefault = 0.1;
  options[OPT_SPINUPTOL].iType = 2;
  options[OPT_SPINUPTOL].iMultiFile = 1;
  fnRead[OPT_SPINUPTOL] = &ReadSpinUpTol;

}

void ReadOptionsPoise(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,SYSTEM *system,fnReadOption fnRead[],int iBody) {
  int iOpt;

  for (iOpt=OPTSTARTPOISE;iOpt<OPTENDPOISE;iOpt++) {
      if (options[iOpt].iType != -1) {
        fnRead[iOpt](body,control,files,&options[iOpt],system,iBody+1);
      }
  }
//   ReadGridOutput(files,options,output,iBody+1,control->Io.iVerbose);
}


/******************* Verify POISE ******************/
void VerifyAlbedo(BODY *body, OPTIONS *options, char cFile[], int iBody, int iVerbose) {
  if (body[iBody].bClimateModel == ANN) {
    /* If all of bColdstart, dFixIceLat, and bAlbedoZA are set, exit */
    if (options[OPT_COLDSTART].iLine[iBody+1] > -1 && options[OPT_FIXICELAT].iLine[iBody+1] > -1 && options[OPT_ALBEDOZA].iLine[iBody+1] > -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Only one of %s, %s, and %s can be set in File: %s\n", options[OPT_COLDSTART].cName, options[OPT_FIXICELAT].cName, options[OPT_ALBEDOZA].cName, cFile);
      exit(EXIT_INPUT);
    }

    /* Any two of bColdstart, dFixIceLat, and bAlbedoZA are set, exit */
    if (options[OPT_COLDSTART].iLine[iBody+1] > -1 && options[OPT_FIXICELAT].iLine[iBody+1] > -1 && options[OPT_ALBEDOZA].iLine[iBody+1] == -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Only one of %s and %s can be set in File: %s\n", options[OPT_COLDSTART].cName, options[OPT_FIXICELAT].cName, cFile);
      exit(EXIT_INPUT);
    }

    if (options[OPT_COLDSTART].iLine[iBody+1] > -1 && options[OPT_FIXICELAT].iLine[iBody+1] == -1 && options[OPT_ALBEDOZA].iLine[iBody+1] > -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Only one of %s and %s can be set in File: %s\n", options[OPT_COLDSTART].cName, options[OPT_ALBEDOZA].cName, cFile);
      exit(EXIT_INPUT);
    }

    if (options[OPT_COLDSTART].iLine[iBody+1] == -1 && options[OPT_FIXICELAT].iLine[iBody+1] > -1 && options[OPT_ALBEDOZA].iLine[iBody+1] > -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Only one of %s and %s can be set in File: %s\n", options[OPT_FIXICELAT].cName, options[OPT_ALBEDOZA].cName, cFile);
      exit(EXIT_INPUT);
    }

    if (options[OPT_ALBEDOLAND].iLine[iBody+1] > -1 || options[OPT_ALBEDOWATER].iLine[iBody+1] > -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Cannot set %s or %s for annual model in file %s\nPlease use option %s\n", options[OPT_ALBEDOLAND].cName, options[OPT_ALBEDOWATER].cName, cFile, options[OPT_SURFALBEDO].cName);
      exit(EXIT_INPUT);
    }

  } else if (body[iBody].bClimateModel == SEA) {
    if (options[OPT_SURFALBEDO].iLine[iBody+1] > -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Cannot set %s for seasonal model in file %s\nPlease use options %s and %s\n",  options[OPT_SURFALBEDO].cName, cFile, options[OPT_ALBEDOLAND].cName, options[OPT_ALBEDOWATER].cName);
      exit(EXIT_INPUT);
    }
  }
}

void VerifyIceSheets(BODY *body, OPTIONS *options, char cFile[], int iBody, int iVerbose) {
  if (body[iBody].bClimateModel == ANN) {
    if (iVerbose >= VERBERR)
      fprintf(stderr,"ERROR: Cannot set %s in annual model in File:%s\n", options[OPT_ICESHEETS].cName, cFile);
    exit(EXIT_INPUT);
  }
}

void VerifyOLR(BODY *body, OPTIONS *options, char cFile[], int iBody, int iVerbose) {
  if (body[iBody].bCalcAB) {
    if (options[OPT_PLANCKA].iLine[iBody+1] > -1 || options[OPT_PLANCKB].iLine[iBody+1] > -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Cannot set %s or %s when setting bCalcAB = 1 in File:%s\n", options[OPT_PLANCKA].cName, options[OPT_PLANCKB].cName, cFile);
      exit(EXIT_INPUT);
    }

  } else {
    if (options[OPT_PCO2].iLine[iBody+1] > -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Cannot set %s unless setting bCalcAB = 1 in File:%s\n", options[OPT_PCO2].cName, cFile);
      exit(EXIT_INPUT);
    }
  }
}

void VerifyNStepSeasonal(BODY *body, int iBody) {
  if (body[iBody].iNStepInYear > body[iBody].iNDays) {
    body[iBody].iNStepInYear = body[iBody].iNDays;
  }
}

void VerifyOrbitOblData(BODY *body,CONTROL *control,OPTIONS *options,int iBody) {
  int iNLines, iLine, c;
  double dttmp, datmp, detmp, ditmp, daptmp, dlatmp, dmatmp, dobltmp, dprecatmp;
  FILE *fileorb;

  if (body[iBody].bReadOrbitOblData) {
    if (options[OPT_FILEORBITOBLDATA].iLine[iBody+1] == -1) {
      fprintf(stderr,"ERROR: Must set %s if using %s for file %s\n",options[OPT_FILEORBITOBLDATA].cName,options[OPT_READORBITOBLDATA].cName,body[iBody].cName);
      exit(EXIT_INPUT);
    } else {
      fileorb = fopen(body[iBody].cFileOrbitOblData,"r");
      if (fileorb == NULL) {
        printf("ERROR: File %s not found.\n", body[iBody].cFileOrbitOblData);
        exit(EXIT_INPUT);
      }
      iNLines = 0;
      while ((c = getc(fileorb)) != EOF) {
        if (c == '\n') iNLines++;              //add 1 for each new line
      }
      rewind(fileorb);

      body[iBody].iNLines = iNLines;
      body[iBody].daTimeSeries = malloc(iNLines*sizeof(double));
      body[iBody].daSemiSeries = malloc(iNLines*sizeof(double));
      body[iBody].daEccSeries = malloc(iNLines*sizeof(double));
      body[iBody].daArgPSeries = malloc(iNLines*sizeof(double));
      body[iBody].daLongASeries = malloc(iNLines*sizeof(double));
      body[iBody].daOblSeries = malloc(iNLines*sizeof(double));
      body[iBody].daPrecASeries = malloc(iNLines*sizeof(double));
      
      body[iBody].daHeccSeries = malloc(iNLines*sizeof(double));
      body[iBody].daKeccSeries = malloc(iNLines*sizeof(double));
      
      printf("file open\n");
      
      iLine = 0;
      while (feof(fileorb) == 0) {
        fscanf(fileorb, "%lf %lf %lf %lf %lf %lf %lf", &dttmp, &datmp, &detmp, &daptmp, &dlatmp, &dobltmp, &dprecatmp);
        
        body[iBody].daTimeSeries[iLine] = dttmp*fdUnitsTime(control->Units[iBody+1].iTime); 
        body[iBody].daSemiSeries[iLine] = datmp*fdUnitsLength(control->Units[iBody+1].iLength);
        body[iBody].daEccSeries[iLine] = detmp;
        
        if (control->Units[iBody+1].iAngle == 0) {
          body[iBody].daArgPSeries[iLine] = daptmp;
          body[iBody].daLongASeries[iLine] = dlatmp;
          body[iBody].daOblSeries[iLine] = dobltmp;
          body[iBody].daPrecASeries[iLine] = dprecatmp;
        } else {
          body[iBody].daArgPSeries[iLine] = daptmp*DEGRAD;
          body[iBody].daLongASeries[iLine] = dlatmp*DEGRAD;
          body[iBody].daOblSeries[iLine] = dobltmp*DEGRAD;
          body[iBody].daPrecASeries[iLine] = dprecatmp*DEGRAD;
        }
        body[iBody].daHeccSeries[iLine] = body[iBody].daEccSeries[iLine]*\
            sin(body[iBody].daArgPSeries[iLine]+body[iBody].daLongASeries[iLine]);
        body[iBody].daKeccSeries[iLine] = body[iBody].daEccSeries[iLine]*\
            cos(body[iBody].daArgPSeries[iLine]+body[iBody].daLongASeries[iLine]);
        
        iLine++;
      }
      fclose(fileorb);
      
    }
    body[iBody].iCurrentStep = 0;
    if (control->Evolve.bVarDt) {
      fprintf(stderr,"ERROR: Cannot use variable time step (%s = 1) if %s = 1\n",options[OPT_VARDT].cName,options[OPT_READORBITDATA].cName);
      exit(EXIT_INPUT);
    }
    if (control->Evolve.bDoForward) {
      if (body[iBody].daTimeSeries[1] != control->Evolve.dTimeStep) {
        fprintf(stderr,"ERROR: Time step size (%s = 1) must match orbital data if %s = 1\n",options[OPT_TIMESTEP].cName,options[OPT_READORBITDATA].cName);
        exit(EXIT_INPUT);
      }
    } else if (control->Evolve.bDoBackward) {
      if (body[iBody].daTimeSeries[1] != -1*control->Evolve.dTimeStep) {
        fprintf(stderr,"ERROR: Time step size (%s = 1) must match orbital data if %s = 1\n",options[OPT_TIMESTEP].cName,options[OPT_READORBITDATA].cName);
        exit(EXIT_INPUT);
      }
    }
    if (iNLines < (control->Evolve.dStopTime/control->Evolve.dTimeStep+1) ) {
      fprintf(stderr,"ERROR: Input orbit data must at least as long as vplanet integration (%f years)\n",control->Evolve.dStopTime/YEARSEC);
      exit(EXIT_INPUT);
    }

  }
}

void InitializeLatGrid(BODY *body, int iBody) {
  double delta_x, SinLat;
  int i;
  delta_x = 2.0/body[iBody].iNumLats;

  body[iBody].daLats = malloc(body[iBody].iNumLats*sizeof(double));

  for (i=0;i<body[iBody].iNumLats;i++) {
    SinLat = (-1.0 + delta_x/2.) + i*delta_x;
    body[iBody].daLats[i] = asin(SinLat);
  }
}

void InitializeLandWater(BODY *body, int iBody) {
  int iLat;

  body[iBody].daLandFrac = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daWaterFrac = malloc(body[iBody].iNumLats*sizeof(double));

  if (body[iBody].iGeography == UNIFORM3) {
    for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
      body[iBody].daLandFrac[iLat] = 0.34;
      body[iBody].daWaterFrac[iLat] = 1.0-body[iBody].daLandFrac[iLat];
    }
  } else if (body[iBody].iGeography == MODERN) {
    for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
      if (body[iBody].daLats[iLat]*180./PI <= -60) {
        body[iBody].daLandFrac[iLat] = 0.95/1.0094;
      } else if (body[iBody].daLats[iLat]*180./PI > -60 && body[iBody].daLats[iLat]*180./PI <= -40) {
        body[iBody].daLandFrac[iLat] = 0.05/1.0094;
      } else if (body[iBody].daLats[iLat]*180./PI > -40 && body[iBody].daLats[iLat]*180./PI <= 20) {
        body[iBody].daLandFrac[iLat] = 0.25/1.0094;
      } else if (body[iBody].daLats[iLat]*180./PI > 20 && body[iBody].daLats[iLat]*180./PI <= 70) {
        body[iBody].daLandFrac[iLat] = 0.5/1.0094;
      } else {
        body[iBody].daLandFrac[iLat] = 0.38/1.0094;
      }
      body[iBody].daWaterFrac[iLat] = 1.0-body[iBody].daLandFrac[iLat];
    }
  }
}

void DampTemp(BODY *body, double dTGlobalTmp, int iBody) {
  int iLat;
  double deltaT = (dTGlobalTmp-body[iBody].dTGlobal)/5.0;

  body[iBody].dAlbedoGlobal = 0.0;

  for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
    body[iBody].daTempLand[iLat]+= deltaT;
    body[iBody].daTempWater[iLat] += deltaT;
  }
  AlbedoSeasonal(body,iBody,0); /* since this is executed only once, we need to multiply
                                    dAlbedoGlobal by iNStepInYear below */
  body[iBody].dAlbedoGlobal = body[iBody].dAlbedoGlobal*body[iBody].iNStepInYear;;
}


void InitializeClimateParams(BODY *body, int iBody, int iVerbose) {
  int i, j, count, iRun;
  double Toffset, xboundary, RunningMeanTmp;
  double *daRunningMean, TotalMean;

  body[iBody].dIceMassTot = 0.0;
  body[iBody].daInsol = malloc(body[iBody].iNumLats*sizeof(double*));
  body[iBody].daAnnualInsol = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daPeakInsol = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].iNDays = (int)floor(body[iBody].dRotRate/body[iBody].dMeanMotion); //number of days in year
  body[iBody].daFlux = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daFluxIn = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daFluxOut = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daDivFlux = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daIceHeight = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daIceFlow = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daIceFlowMid = malloc((body[iBody].iNumLats+1)*sizeof(double));
  body[iBody].daDIceHeightDy = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daDeclination = malloc(body[iBody].iNDays*sizeof(double));
  body[iBody].daTGrad = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daDMidPt = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daDeltaTempL = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daDeltaTempW = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daEnergyResL = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daEnergyResW = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daEnerResLAnn = malloc(body[iBody].iNumLats*sizeof(double));
  body[iBody].daEnerResWAnn = malloc(body[iBody].iNumLats*sizeof(double));

  /* initialize some output quantities to zero to avoid memory errors */
  body[iBody].dFluxInGlobal = 0;
  body[iBody].bSkipSeas = 0;
  body[iBody].dFluxOutGlobal = 0;
  body[iBody].dIceMassTot = 0;
  body[iBody].dIceFlowTot = 0;
  body[iBody].dIceBalanceTot = 0;
  /*-------------------------------------------------------------------*/

  body[iBody].bSnowball = 0;
  body[iBody].dFluxInGlobal = 0;
  body[iBody].dIceFlowTot = 0;
  body[iBody].dIceBalanceTot = 0;
  body[iBody].iWriteLat = 0;

  if (body[iBody].bColdStart) {
    Toffset = -40.0;
  } else {
    Toffset = 0.0;
  }
  body[iBody].dTGlobal = 0.0;
  body[iBody].dAlbedoGlobal = 0.0;

  if (body[iBody].bDistRot == 0) {
    body[iBody].dPrecA0 = body[iBody].dPrecA;
  }

  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeasEnabled) {
    body[iBody].daDiffusionAnn = malloc((body[iBody].iNumLats+1)*sizeof(double));
    body[iBody].daLambdaAnn = malloc((body[iBody].iNumLats+1)*sizeof(double));
    body[iBody].daAlbedoAnn = malloc(body[iBody].iNumLats*sizeof(double));
    //body[iBody].iNDays = 360;
    body[iBody].daMDiffAnn = malloc(body[iBody].iNumLats*sizeof(double*)); // matrix of heat diffusion terms only
    body[iBody].daTempAnn = malloc(body[iBody].iNumLats*sizeof(double));

    body[iBody].daPlanckAAnn = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daPlanckBAnn = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daMClim = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daMEulerAnn = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daMEulerCopyAnn = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daInvMAnn = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daSourceF = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempTerms = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTmpTempAnn = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTmpTempTerms = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].iaRowswapAnn =  malloc(body[iBody].iNumLats*sizeof(int));
    body[iBody].daScaleAnn = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daUnitVAnn = malloc(body[iBody].iNumLats*sizeof(double));

    body[iBody].daDiffusionAnn[0] = body[iBody].dDiffCoeff;
    for (i=0;i<=body[iBody].iNumLats;i++) {
      if (i!=body[iBody].iNumLats) {
        body[iBody].daTempAnn[i] = 20.*(1.0-1.5*sin(body[iBody].daLats[i])*sin(body[iBody].daLats[i]))+Toffset;
        body[iBody].dTGlobal += body[iBody].daTempAnn[i]/body[iBody].iNumLats;
        body[iBody].daInsol[i] = malloc(body[iBody].iNDays*sizeof(double));
        body[iBody].daMClim[i] = malloc(body[iBody].iNumLats*sizeof(double));
        body[iBody].daMDiffAnn[i] = malloc(body[iBody].iNumLats*sizeof(double));
        body[iBody].daMEulerAnn[i] = malloc(body[iBody].iNumLats*sizeof(double));
        body[iBody].daMEulerCopyAnn[i] = malloc(body[iBody].iNumLats*sizeof(double));
        body[iBody].daInvMAnn[i] = malloc(body[iBody].iNumLats*sizeof(double));
      }

      if (body[iBody].bCalcAB) {
        /* Calculate A and B from williams and kasting 97 result */
        body[iBody].daPlanckBAnn[i] = dOLRdTwk97(body,iBody,i,ANN);
        body[iBody].daPlanckAAnn[i] = OLRwk97(body,iBody,i,ANN) \
          - body[iBody].daPlanckBAnn[i]*(body[iBody].daTempAnn[i]);
      } else {
        body[iBody].daPlanckBAnn[i] = body[iBody].dPlanckB;
        body[iBody].daPlanckAAnn[i] = body[iBody].dPlanckA;
      }

      if (body[iBody].bMEPDiff) {
        if (i==0) {
          body[iBody].daDiffusionAnn[i] = body[iBody].daPlanckBAnn[i]/4.0;
        } else if (i==body[iBody].iNumLats) {
          body[iBody].daDiffusionAnn[i] = body[iBody].daPlanckBAnn[i-1]/4.0;
        } else {
          body[iBody].daDiffusionAnn[i] = (body[iBody].daPlanckBAnn[i]+body[iBody].daPlanckBAnn[i-1])/8.0;
        }
      } else if (body[iBody].bDiffRot) {
        body[iBody].daDiffusionAnn[i] = body[iBody].dDiffCoeff/\
          (body[iBody].dRotRate*body[iBody].dRotRate/(4*PI*PI/DAYSEC/DAYSEC));
      } else {
        body[iBody].daDiffusionAnn[i] = body[iBody].dDiffCoeff;
      }

      if (body[iBody].bHadley) {
        // XXX not self-consistent with rotation rate!
        xboundary = -1.0 + i*2.0/body[iBody].iNumLats;
        body[iBody].daDiffusionAnn[i] += body[iBody].dDiffCoeff*9.*exp(-pow((xboundary/sin(25.*DEGRAD)),6));
      }
    }

    if (body[iBody].bClimateModel == SEA) {
      body[iBody].dSurfAlbedo = (body[iBody].dAlbedoLand + body[iBody].dAlbedoWater)/2.0;
    }

    AlbedoAnnual(body,iBody);
    for (i=0;i<body[iBody].iNumLats;i++) {
      body[iBody].dAlbedoGlobal += body[iBody].daAlbedoAnn[i];
    }
    body[iBody].dAlbedoGlobal /= body[iBody].iNumLats;
    PoiseAnnual(body,iBody);
  }

  if (body[iBody].bClimateModel == SEA) {
    /* oh yeah, seasonal model, oh yeah!
    'tis the season to model ice sheets, fa la la la la, la la la la */

    /* First, if annual predict RGH or snowball, skip seasonal */
    if (body[iBody].bSkipSeasEnabled) {
      if (body[iBody].dFluxOutGlobal >= 300 || body[iBody].dAlbedoGlobal >= body[iBody].dIceAlbedo) {
        body[iBody].bSkipSeas = 1;
      } else {
        body[iBody].bSkipSeas = 0;
      }
    } else {
      body[iBody].bSkipSeas = 0;
    }
    VerifyNStepSeasonal(body,iBody);
    body[iBody].dHeatCapWater *= body[iBody].dMixingDepth;
    body[iBody].dTGlobal = 0.0;
    body[iBody].dSeasDeltax = 2.0/body[iBody].iNumLats;
    body[iBody].dSeasDeltat = 1./body[iBody].iNStepInYear;
    body[iBody].daXBoundary = malloc((body[iBody].iNumLats+1)*sizeof(double));
    body[iBody].daTempLand = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempWater = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempLW = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempMaxLW = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempMaxLand = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempMaxWater = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempMinLW = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempDaily = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daFluxOutLand = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxOutWater = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxInLand = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxInWater = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daSeaIceHeight = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daMEulerSea = malloc(2*body[iBody].iNumLats*sizeof(double*));
    body[iBody].daMEulerCopySea = malloc(2*body[iBody].iNumLats*sizeof(double*));
    body[iBody].daMInit = malloc(2*body[iBody].iNumLats*sizeof(double*));
    body[iBody].daInvMSea = malloc(2*body[iBody].iNumLats*sizeof(double*));
    body[iBody].daSourceL = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daSourceW = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daSourceLW = malloc(2*body[iBody].iNumLats*sizeof(double));
    body[iBody].daMLand = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daMWater = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daMDiffSea = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].iaRowswapSea =  malloc(2*body[iBody].iNumLats*sizeof(int));
    body[iBody].daScaleSea = malloc(2*body[iBody].iNumLats*sizeof(double));
    body[iBody].daUnitVSea = malloc(2*body[iBody].iNumLats*sizeof(double));
    body[iBody].daAlbedoLand = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daAlbedoWater = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daLambdaSea = malloc((body[iBody].iNumLats+1)*sizeof(double));
    body[iBody].daAlbedoLW = malloc(body[iBody].iNumLats*sizeof(double));
    //body[iBody].daAlbedoGlobalTmp = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTmpTempSea = malloc(2*body[iBody].iNumLats*sizeof(double));
    //body[iBody].daTGlobalTmp = malloc(body[iBody].iNDays*sizeof(double));
    body[iBody].daSeaIceHeight = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daSeaIceK = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxSeaIce = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daAlbedoAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxInAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daDivFluxAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxOutAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempAvgL = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daAlbedoAvgL = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daTempAvgW = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daAlbedoAvgW = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxDaily = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daFluxInAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxInDaily = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daDivFluxAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daDivFluxDaily = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daFluxOutAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daFluxOutDaily = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daIceBalance = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daIceMass = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daIceBalanceAnnual = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daIceMassTmp = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daSedShear = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daBasalVel = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daBasalFlow = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daBasalFlowMid = malloc((body[iBody].iNumLats+1)*sizeof(double));
    body[iBody].daIcePropsTmp = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daIceGamTmp = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daIceSheetDiff = malloc((body[iBody].iNumLats+1)*sizeof(double));
    body[iBody].daIceSheetMat = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daIceBalanceTmp = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daYBoundary = malloc((body[iBody].iNumLats+1)*sizeof(double));
    body[iBody].daIceBalanceAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daIceFlowAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daBedrockH = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daBedrockHEq = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daPlanckASea = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daPlanckBSea = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daDiffusionSea = malloc((body[iBody].iNumLats+1)*sizeof(double));
    body[iBody].daPlanckBDaily = malloc(body[iBody].iNumLats*sizeof(double*));
    body[iBody].daPlanckBAvg = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daIceAccumTot = malloc(body[iBody].iNumLats*sizeof(double));
    body[iBody].daIceAblateTot = malloc(body[iBody].iNumLats*sizeof(double));

    InitializeLandWater(body,iBody);
    body[iBody].dLatFHeatCp = 83.5;  //CC sez this is about right
    body[iBody].dLatentHeatIce = body[iBody].dHeatCapWater*body[iBody].dLatFHeatCp/body[iBody].dMixingDepth;

    for (i=0;i<=body[iBody].iNumLats;i++) {
      if (i!=body[iBody].iNumLats) {
        body[iBody].daTempLand[i] = (body[iBody].dTGlobalInit-7.35) + 20.*(1.0-2*sin(body[iBody].daLats[i])*sin(body[iBody].daLats[i])) + Toffset;
        body[iBody].daTempWater[i] = (body[iBody].dTGlobalInit-7.35) + 20.*(1.0-2*sin(body[iBody].daLats[i])*sin(body[iBody].daLats[i])) + Toffset;
        body[iBody].daTempLW[i] = body[iBody].daLandFrac[i]*body[iBody].daTempLand[i] + \
                                  body[iBody].daWaterFrac[i]*body[iBody].daTempWater[i];
        if ((body[iBody].daTempWater[i] < body[iBody].dFrzTSeaIce) && (body[iBody].bSeaIceModel)) {
          body[iBody].daSeaIceHeight[i] = 2.0;
        } else {
          body[iBody].daSeaIceHeight[i] = 0.0;
        }

        body[iBody].dTGlobal += (body[iBody].daLandFrac[i]*body[iBody].daTempLand[i]+ \
                 body[iBody].daWaterFrac[i]*body[iBody].daTempWater[i])/body[iBody].iNumLats;
        body[iBody].daTempDaily[i] = malloc(body[iBody].iNumYears*body[iBody].iNStepInYear*sizeof(double));
        body[iBody].daFluxDaily[i] = malloc(body[iBody].iNumYears*body[iBody].iNStepInYear*sizeof(double));
        body[iBody].daFluxInDaily[i] = malloc(body[iBody].iNumYears*body[iBody].iNStepInYear*sizeof(double));
        body[iBody].daFluxOutDaily[i] = malloc(body[iBody].iNumYears*body[iBody].iNStepInYear*sizeof(double));
        body[iBody].daDivFluxDaily[i] = malloc(body[iBody].iNumYears*body[iBody].iNStepInYear*sizeof(double));
        body[iBody].daIceBalance[i] = malloc(body[iBody].iNStepInYear*sizeof(double));
        body[iBody].daMLand[i] = malloc(body[iBody].iNumLats*sizeof(double));
        body[iBody].daMWater[i] = malloc(body[iBody].iNumLats*sizeof(double));
        body[iBody].daMDiffSea[i] = malloc(body[iBody].iNumLats*sizeof(double));
        body[iBody].daIceSheetMat[i] = malloc(body[iBody].iNumLats*sizeof(double));
        body[iBody].daInsol[i] = malloc(body[iBody].iNDays*sizeof(double));
        body[iBody].daPlanckBDaily[i] = malloc(body[iBody].iNumYears*body[iBody].iNStepInYear*sizeof(double));

        /* Seasonal matrix is 2n x 2n to couple land and ocean */
        body[iBody].daMEulerSea[2*i] = malloc(2*body[iBody].iNumLats*sizeof(double));
        body[iBody].daMInit[2*i] = malloc(2*body[iBody].iNumLats*sizeof(double));
        body[iBody].daMEulerCopySea[2*i] = malloc(2*body[iBody].iNumLats*sizeof(double));
        body[iBody].daInvMSea[2*i] = malloc(2*body[iBody].iNumLats*sizeof(double));
        body[iBody].daMEulerSea[2*i+1] = malloc(2*body[iBody].iNumLats*sizeof(double));
        body[iBody].daMInit[2*i+1] = malloc(2*body[iBody].iNumLats*sizeof(double));
        body[iBody].daMEulerCopySea[2*i+1] = malloc(2*body[iBody].iNumLats*sizeof(double));
        body[iBody].daInvMSea[2*i+1] = malloc(2*body[iBody].iNumLats*sizeof(double));

        body[iBody].daIceMassTmp[i] = 0.0;
        body[iBody].daIceBalanceAvg[i] = 0.0;
        body[iBody].daIceFlowAvg[i] = 0.0;
        body[iBody].daBedrockH[i] = 0.0;
        body[iBody].daBedrockHEq[i] = 0.0;
        body[iBody].daIceHeight[i] = 0.0;
        body[iBody].daDIceHeightDy[i] = 0.0;

        body[iBody].daScaleSea[2*i] = 0.;
        body[iBody].daScaleSea[2*i+1] = 0.;
        for (j=0;j<2*body[iBody].iNumLats;j++) {
          body[iBody].daMInit[2*i][j] = 0.;
          body[iBody].daMEulerSea[2*i][j] = 0.;
          body[iBody].daMEulerCopySea[2*i][j] = 0.;
          body[iBody].daMInit[2*i+1][j] = 0.;
          body[iBody].daMEulerSea[2*i+1][j] = 0.;
          body[iBody].daMEulerCopySea[2*i+1][j] = 0.;
        }

        if (body[iBody].bIceSheets) {
          if (fabs(body[iBody].daLats[i])>=(body[iBody].dInitIceLat*DEGRAD)) {
            body[iBody].daBedrockH[i] = 0.0;
            body[iBody].daBedrockHEq[i] = 0.0;
            body[iBody].daIceMass[i] = body[iBody].dInitIceHeight*RHOICE;
            body[iBody].daIceMassTmp[i] = body[iBody].daIceMass[i]; //needs to be set if starting with ice, since this is the array that AlbedoSeasonal uses
            body[iBody].dIceMassTot += body[iBody].daIceMass[i]*(2*PI*body[iBody].dRadius*body[iBody].dRadius*(sin(body[iBody].daLats[1])-sin(body[iBody].daLats[0]))); //XXX only works if all lat cells are equal area!!
  //           body[iBody].daIceHeight[i] = body[iBody].dInitIceHeight;
          } else {
            body[iBody].daIceMass[i] = 0.0;
  //           body[iBody].daIceHeight[i] = 0.0;
          }
        }
        if (body[iBody].bCalcAB) {
          if (body[iBody].iOLRModel == WK97) {
            /* Calculate A and B from williams and kasting 97 result */
            body[iBody].daPlanckBSea[i] = dOLRdTwk97(body,iBody,i,SEA);
            body[iBody].daPlanckBAvg[i] = body[iBody].daPlanckBSea[i];
            body[iBody].daPlanckASea[i] = OLRwk97(body,iBody,i,SEA) \
              - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
          } else if (body[iBody].iOLRModel == HM16) {
            /* Calculate A and B from haqq-misra+ 2016 result */
            body[iBody].daPlanckBSea[i] = dOLRdThm16(body,iBody,i,SEA);
            body[iBody].daPlanckBAvg[i] = body[iBody].daPlanckBSea[i];
            body[iBody].daPlanckASea[i] = OLRhm16(body,iBody,i,SEA) \
              - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
          } else {
            /* Calculate A and B from haqq-misra+ 2016 result */
            body[iBody].daPlanckBSea[i] = dOLRdTsms09(body,iBody,i,SEA);
            body[iBody].daPlanckBAvg[i] = body[iBody].daPlanckBSea[i];
            body[iBody].daPlanckASea[i] = OLRsms09(body,iBody,i,SEA) \
              - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
          }
        } else {
          body[iBody].daPlanckBSea[i] = body[iBody].dPlanckB;
          body[iBody].daPlanckBAvg[i] = body[iBody].daPlanckBSea[i];
          body[iBody].daPlanckASea[i] = body[iBody].dPlanckA;
        }
      }

      if (body[iBody].bMEPDiff) {
        if (i==0) {
          body[iBody].daDiffusionSea[i] = body[iBody].daPlanckBSea[i]/4.0;
        } else if (i==body[iBody].iNumLats) {
          body[iBody].daDiffusionSea[i] = body[iBody].daPlanckBSea[i-1]/4.0;
        } else {
          body[iBody].daDiffusionSea[i] = (body[iBody].daPlanckBSea[i]+body[iBody].daPlanckBSea[i-1])/8.0;
        }
      } else if (body[iBody].bDiffRot) {
        body[iBody].daDiffusionSea[i] = body[iBody].dDiffCoeff/\
          (body[iBody].dRotRate*body[iBody].dRotRate/(4*PI*PI/DAYSEC/DAYSEC));
      } else {
        body[iBody].daDiffusionSea[i] = body[iBody].dDiffCoeff;
      }

      body[iBody].daXBoundary[i] = -1.0 + i*2.0/body[iBody].iNumLats;
      body[iBody].daYBoundary[i] = body[iBody].dRadius*body[iBody].dSeasDeltax/sqrt(1.0-body[iBody].daXBoundary[i]*body[iBody].daXBoundary[i]);
      if (body[iBody].bHadley) {
        // XXX not self-consistent with rotation rate!
        body[iBody].daDiffusionSea[i] += body[iBody].dDiffCoeff*9.*exp(-pow((body[iBody].daXBoundary[i]/sin(25.*DEGRAD)),6));
      }
    }

    if (body[iBody].bSkipSeas == 0) {
      AnnualInsolation(body, iBody);
      AlbedoSeasonal(body,iBody,0); /* since this is executed only once, we need to multiply
                                    dAlbedoGlobal by iNStepInYear below */
      body[iBody].dAlbedoGlobal = body[iBody].dAlbedoGlobal*body[iBody].iNStepInYear;
      MatrixSeasonal(body, iBody);
      SourceFSeas(body,iBody,0);
      if (body[iBody].bSeaIceModel) {
        SeaIce(body,iBody);
      }

      /* "burn in" to a quasi equilibrium */
      //TGlobalTmp = 0;
      /* This was old code -- Is it needed?
      while (fabs(TGlobalTmp - body[iBody].dTGlobal) > 0.01) {
        TGlobalTmp = body[iBody].dTGlobal;
        PoiseSeasonal(body,iBody);
        printf("TGlobal = %f\n",TGlobalTmp);
      */
      count = 0;
      int RunLen = 5;
      daRunningMean = malloc((RunLen+1)*sizeof(double));
      daRunningMean[RunLen] = 0;
      TotalMean = 0;
      RunningMeanTmp = daRunningMean[RunLen];
      while (fabs(RunningMeanTmp - daRunningMean[RunLen]) > body[iBody].dSpinUpTol || count <= 2*RunLen) {
        RunningMeanTmp = daRunningMean[RunLen];
        PoiseSeasonal(body,iBody);
        MatrixSeasonal(body,iBody);
        Snowball(body,iBody);

        if (count < RunLen) {
          daRunningMean[count] = body[iBody].dTGlobal;
          if (iVerbose >= VERBINPUT)
            printf("TGlobal = %f\n",daRunningMean[count]);
        } else {
//           DampTemp(body,RunningMeanTmp,iBody);
          daRunningMean[RunLen] = 0;
          for (iRun = 0; iRun < RunLen-1; iRun++) {
            daRunningMean[iRun] = daRunningMean[iRun+1];
            daRunningMean[RunLen] += daRunningMean[iRun];
          }
          daRunningMean[RunLen-1] = body[iBody].dTGlobal;
          daRunningMean[RunLen] += daRunningMean[RunLen-1];
          daRunningMean[RunLen] /= RunLen;
//           TotalMean *= (float)(count-RunLen)/(count-RunLen+1);
//           TotalMean += daRunningMean[RunLen-1]/(count-RunLen+1);
          if (iVerbose >= VERBINPUT)
            printf("TGlobal = %f; Prev RunningMean = %f; Curr RunningMean = %f \n",daRunningMean[RunLen-1],RunningMeanTmp,daRunningMean[RunLen]);
        }
        count += 1;
      }
      free(daRunningMean);

    } else if (body[iBody].bSkipSeas == 1) {
      printf("Planet started in RGH or snowball, skipping Seasonal model\n");
    }
  }
}

void VerifyAstro(BODY *body, OPTIONS *options, char cFile[], int iBody, int iVerbose) {
  if (body[iBody].bEqtide == 0) {
    if (body[iBody].bDistOrb == 0) {
      CalcHK(body, iBody);
    }
    if (body[iBody].bDistRot == 0) {
      CalcXYZobl(body,iBody);
    }
  }
  if (body[iBody].bForceObliq == 1) {
    if (body[iBody].bDistRot == 1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Cannot set %s == 1 when using DistRot in File:%s\n", options[OPT_FORCEOBLIQ].cName, cFile);
      exit(EXIT_INPUT);
    } else {
      body[iBody].dObliq0 = body[iBody].dObliquity;
    }
    if (body[iBody].dObliqAmp*DEGRAD > body[iBody].dObliq0) {
        fprintf(stderr,"ERROR: %s > %s is not allowed.\n", options[OPT_OBLIQAMP].cName,options[OPT_OBL].cName);
        DoubleLineExit(cFile,cFile,options[OPT_OBLIQAMP].iLine[iBody + 1],options[OPT_OBL].iLine[iBody + 1]);
    }
  }
  if (body[iBody].bForceEcc == 1) {
    if (body[iBody].bDistRot == 1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Cannot set %s == 1 when using DistRot in File:%s\n", options[OPT_FORCEECC].cName, cFile);
      exit(EXIT_INPUT);
    } else {
      body[iBody].dEcc0 = body[iBody].dEcc;
    }
    if (body[iBody].dEccAmp > body[iBody].dEcc) {
        fprintf(stderr,"ERROR: %s > %s is not allowed.\n", options[OPT_ECCAMP].cName,options[OPT_ORBECC].cName);
        DoubleLineExit(cFile,cFile,options[OPT_ECCAMP].iLine[iBody + 1],options[OPT_ORBECC].iLine[iBody + 1]);
    }
  }
}

void VerifyDiffusion(BODY *body, OPTIONS *options, char cFile[], int iBody, int iVerbose) {
  if (body[iBody].bMEPDiff) {
    if (options[OPT_DIFFUSION].iLine[iBody+1] > -1) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Cannot set %s when setting bMEPDiff = 1 in File:%s\n", options[OPT_DIFFUSION].cName, cFile);
      exit(EXIT_INPUT);
    }
    if (body[iBody].bHadley) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: Cannot set both bHadley = 1 and bMEPDiff = 1 in File:%s\n", cFile);
      exit(EXIT_INPUT);
    }
  }
}

void VerifySeasOutputTime(BODY *body,CONTROL *control,OPTIONS *options,char cFile[],int iBody,int iVerbose) {
  if (body[iBody].dSeasOutputTime != 0) {
    if (body[iBody].dSeasOutputTime < control->Io.dOutputTime) {
      if (iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: %s in file %s must be greater than or equal to %s \n", options[OPT_SEASOUTPUTTIME].cName, cFile,options[OPT_OUTPUTTIME].cName);
      exit(EXIT_INPUT);
    }
  }
}

void AssignPoiseDerivatives(BODY *body,EVOLVE *evolve,UPDATE *update,fnUpdateVariable ***fnUpdate,int iBody) {
//  Nothing here, because entire climate simulation is ran in ForceBehavior

//  if (body[iBody].bIceSheets) {
//     for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
//       fnUpdate[iBody][update[iBody].iaIceMass[iLat]][update[iBody].iaIceMassDepMelt[iLat]] = &fdPoiseDIceMassDtDepMelt;
//       fnUpdate[iBody][update[iBody].iaIceMass[iLat]][update[iBody].iaIceMassFlow[iLat]] = &fdPoiseDIceMassDtFlow;
//     }
//  }
}

void NullPoiseDerivatives(BODY *body,EVOLVE *evolve,UPDATE *update,fnUpdateVariable ***fnUpdate,int iBody) {
//  Nothing here, because entire climate simulation is ran in ForceBehavior

//  if (body[iBody].bIceSheets) {
//     for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
//       fnUpdate[iBody][update[iBody].iaIceMass[iLat]][update[iBody].iaIceMassDepMelt[iLat]] = &fndUpdateFunctionTiny;
//       fnUpdate[iBody][update[iBody].iaIceMass[iLat]][update[iBody].iaIceMassFlow[iLat]] = &fndUpdateFunctionTiny;
//     }
//  }
}


void VerifyPoise(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,OUTPUT *output,SYSTEM *system,UPDATE *update,int iBody,int iModule) {
  int i, j=0, iLat=0;

  VerifyAlbedo(body,options,files->Infile[iBody+1].cIn,iBody,control->Io.iVerbose);
  VerifyAstro(body,options,files->Infile[iBody+1].cIn,iBody,control->Io.iVerbose);
  VerifyOrbitOblData(body, control, options, iBody);

  VerifyOLR(body,options,files->Infile[iBody+1].cIn,iBody,control->Io.iVerbose);
  VerifyDiffusion(body,options,files->Infile[iBody+1].cIn,iBody,control->Io.iVerbose);
  VerifySeasOutputTime(body,control,options,files->Infile[iBody+1].cIn,iBody,control->Io.iVerbose);
  if (body[iBody].bDistRot == 0) {
    VerifyDynEllip(body,control,options,files->Infile[iBody+1].cIn,iBody,control->Io.iVerbose);
  }

  /* Initialize climate arrays */
  InitializeLatGrid(body, iBody);
  InitializeClimateParams(body,iBody,control->Io.iVerbose);

  /* The climate simulation is done entirely in ForceBehavior. */
  if (body[iBody].bIceSheets) {
    VerifyIceSheets(body,options,files->Infile[iBody+1].cIn,iBody,control->Io.iVerbose);
//     for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
//       InitializeIceMassDepMelt(body,update,iBody,iLat);
//       fnUpdate[iBody][update[iBody].iaIceMass[iLat]][update[iBody].iaIceMassDepMelt[iLat]] = &fdPoiseDIceMassDtDepMelt;
//       InitializeIceMassFlow(body,update,iBody,iLat);
//       fnUpdate[iBody][update[iBody].iaIceMass[iLat]][update[iBody].iaIceMassFlow[iLat]] = &fdPoiseDIceMassDtFlow;
//     }
  }

  control->fnPropsAux[iBody][iModule] = &PropsAuxPoise;

  control->fnForceBehavior[iBody][iModule]=&ForceBehaviorPoise;
  control->Evolve.fnBodyCopy[iBody][iModule]=&BodyCopyPoise;
}


/***************** POISE Update *****************/
void InitializeUpdatePoise(BODY *body,UPDATE *update,int iBody) {
  
}

void FinalizeUpdateIceMassPoise(BODY *body,UPDATE *update,int *iEqn,int iVar,int iBody,int iLat) {
}

/***************** POISE Halts *****************/

void CountHaltsPoise(HALT *halt,int *iNumHalts) {
}

void VerifyHaltPoise(BODY *body,CONTROL *control,OPTIONS *options,int iBody,int *iHalt) {
}

/* Minimum ice flow time-step? */
// int HaltMinIceDt(BODY *body,EVOLVE *evolve,HALT *halt,IO *io,UPDATE *update,int iBody) {
// }

/************* POISE Outputs ******************/

void WriteTGlobal(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  /* Get TGlobal */
  *dTmp = body[iBody].dTGlobal;
  if (output->bDoNeg[iBody]) {
    /* Units already in Celsius (POISE uses Celsius) */
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp = fdUnitsTemp(*dTmp, 1, 0);
    fsUnitsTime(0,cUnit);
  }
}

void WriteAlbedoGlobal(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  /* Get AlbedoGlobal */
  *dTmp = body[iBody].dAlbedoGlobal;
}

void WriteSnowball(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  /* Get snowball status */
  *dTmp = (double)body[iBody].bSnowball;
}

void WriteSkipSeas(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  /* Get AlbedoGlobal */
  *dTmp = body[iBody].bSkipSeas;
}

void WriteTempLat(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daTempAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daTempAvg[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    /* Units already in Celsius (POISE uses Celsius) */
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp = fdUnitsTemp(*dTmp, 1, 0);
    fsUnitsTime(0,cUnit);
  }
}

void WriteTempMinLat(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daTempAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daTempMinLW[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    /* Units already in Celsius (POISE uses Celsius) */
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp = fdUnitsTemp(*dTmp, 1, 0);
    fsUnitsTime(0,cUnit);
  }
}

void WriteTempMaxLat(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daTempAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daTempMaxLW[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    /* Units already in Celsius (POISE uses Celsius) */
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp = fdUnitsTemp(*dTmp, 1, 0);
    fsUnitsTime(0,cUnit);
  }
}

void WriteTempMaxLand(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daTempAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daTempMaxLand[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    /* Units already in Celsius (POISE uses Celsius) */
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp = fdUnitsTemp(*dTmp, 1, 0);
    fsUnitsTime(0,cUnit);
  }
}

void WriteTempMaxWater(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daTempAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daTempMaxWater[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    /* Units already in Celsius (POISE uses Celsius) */
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp = fdUnitsTemp(*dTmp, 1, 0);
    fsUnitsTime(0,cUnit);
  }
}

void WriteTempLandLat(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daTempAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daTempAvgL[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    /* Units already in Celsius (POISE uses Celsius) */
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp = fdUnitsTemp(*dTmp, 1, 0);
    fsUnitsTime(0,cUnit);
  }
}

void WriteTempWaterLat(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daTempAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daTempAvgW[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    /* Units already in Celsius (POISE uses Celsius) */
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp = fdUnitsTemp(*dTmp, 1, 0);
    fsUnitsTime(0,cUnit);
  }
}

void WriteLatitude(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].daLats[body[iBody].iWriteLat];

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsAngle(units->iAngle);
    fsUnitsAngle(units->iAngle,cUnit);
  }
}

void WriteAlbedoLat(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daAlbedoAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daAlbedoAvg[body[iBody].iWriteLat];
  }
}

void WriteAlbedoLandLat(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daAlbedoAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daAlbedoAvgL[body[iBody].iWriteLat];
  }
}

void WriteAlbedoWaterLat(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daAlbedoAnn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daAlbedoAvgW[body[iBody].iWriteLat];
  }
}

void WriteFluxInGlobal(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].dFluxInGlobal;

  if (output->bDoNeg[iBody]) {
    // Negative option is SI
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime,units->iMass,units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteFluxOutGlobal(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].dFluxOutGlobal;

  if (output->bDoNeg[iBody]) {
    // Negative option is SI
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime,units->iMass,units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteTotIceMass(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].dIceMassTot;

  if (output->bDoNeg[iBody]) {
    // Negative option is SI
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsMass(units->iMass);
    fsUnitsMass(units->iMass,cUnit);
  }
}

void WriteIceFlowTot(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].dIceFlowTot;

  if (output->bDoNeg[iBody]) {
    // Negative option is SI
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsMass(units->iMass);
    fsUnitsMass(units->iMass,cUnit);
  }
}

void WriteAreaIceCov(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  AreaIceCovered(body,iBody);
  *dTmp = body[iBody].dAreaIceCov;

  // if (output->bDoNeg[iBody]) {
//     // Negative option is SI
//     strcpy(cUnit,output->cNeg);
//   } else {
//     *dTmp /= fdUnitsMass(units->iMass);
//     fsUnitsMass(units->iMass,cUnit);
//   }
}

void WriteIceBalanceTot(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].dIceBalanceTot;

  if (output->bDoNeg[iBody]) {
    // Negative option is SI
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsMass(units->iMass);
    fsUnitsMass(units->iMass,cUnit);
  }
}

void WriteAnnualInsol(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].daAnnualInsol[body[iBody].iWriteLat];

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime, units->iMass, units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void WritePeakInsol(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  *dTmp = body[iBody].daPeakInsol[body[iBody].iWriteLat];

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime, units->iMass, units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteDailyInsol(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  char cOut[3*NAMELEN];
  FILE *fp;
  int iLat,iDay;
  double dTime;

  struct stat st = {0};
  if (stat("SeasonalClimateFiles",&st) == -1) {
#ifdef _WIN32
    mkdir("SeasonalClimateFiles");
#else
    mkdir("SeasonalClimateFiles",0700);
#endif
  }

  dTime = control->Evolve.dTime/fdUnitsTime(units->iTime);

  if (dTime == 0) {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.DailyInsol.0",system->cName,body[iBody].cName);
  } else if (dTime < 10000) {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.DailyInsol.%.0f",system->cName,body[iBody].cName,dTime);
  } else {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.DailyInsol.%.2e",system->cName,body[iBody].cName,dTime);
  }

  fp = fopen(cOut,"w");
  for (iDay=0;iDay<body[iBody].iNDays;iDay++) {
    for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
      fprintd(fp,body[iBody].daInsol[iLat][iDay],control->Io.iSciNot,control->Io.iDigits);
      fprintf(fp," ");
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
}

void WritePlanckB(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  char cOut[3*NAMELEN];
  FILE *fp;
  int iLat,iDay;
  double dTime;

  struct stat st = {0};
  if (stat("SeasonalClimateFiles",&st) == -1) {
#ifdef _WIN32
    mkdir("SeasonalClimateFiles");
#else
    mkdir("SeasonalClimateFiles",0700);
#endif
  }

  dTime = control->Evolve.dTime/fdUnitsTime(units->iTime);

  if (dTime == 0) {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.PlanckB.0",system->cName,body[iBody].cName);
  } else if (dTime < 10000) {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.PlanckB.%.0f",system->cName,body[iBody].cName,dTime);
  } else {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.PlanckB.%.2e",system->cName,body[iBody].cName,dTime);
  }

  fp = fopen(cOut,"w");
  for (iDay=0;iDay<body[iBody].iNumYears*body[iBody].iNStepInYear;iDay++) {
    for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
      fprintd(fp,body[iBody].daPlanckBDaily[iLat][iDay],control->Io.iSciNot,control->Io.iDigits);
      fprintf(fp," ");
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
}

void WriteSeasonalTemp(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  char cOut[3*NAMELEN];
  FILE *fp;
  int iLat,iDay;

  double dTime;

  struct stat st = {0};
  if (stat("SeasonalClimateFiles",&st) == -1) {
#ifdef _WIN32
    mkdir("SeasonalClimateFiles");
#else
    mkdir("SeasonalClimateFiles",0700);
#endif
  }

  dTime = control->Evolve.dTime/fdUnitsTime(units->iTime);

  if (dTime == 0) {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.SeasonalTemp.0",system->cName,body[iBody].cName);
  } else if (dTime < 10000) {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.SeasonalTemp.%.0f",system->cName,body[iBody].cName,dTime);
  } else {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.SeasonalTemp.%.2e",system->cName,body[iBody].cName,dTime);
  }

  fp = fopen(cOut,"w");
  for (iDay=0;iDay<body[iBody].iNumYears*body[iBody].iNStepInYear;iDay++) {
    for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
      //printf("%d %d\n",iLat,iDay);
      //printf("%d %d %lf\n",iLat,iDay,body[iBody].daTempDaily[iLat][iDay]);
      fprintd(fp,body[iBody].daTempDaily[iLat][iDay],control->Io.iSciNot,control->Io.iDigits);
      fprintf(fp," ");
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
}

void WriteSeasonalFluxes(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  char cOutM[3*NAMELEN], cOutI[3*NAMELEN], cOutO[3*NAMELEN], cOutD[3*NAMELEN];
  FILE *fpM, *fpI, *fpO, *fpD ;
  int iLat,iDay;

  double dTime;

  struct stat st = {0};
  if (stat("SeasonalClimateFiles",&st) == -1) {
#ifdef _WIN32
    mkdir("SeasonalClimateFiles");
#else
    mkdir("SeasonalClimateFiles",0700);
#endif
  }

  dTime = control->Evolve.dTime/fdUnitsTime(units->iTime);

  if (dTime == 0) {
    sprintf(cOutM,"SeasonalClimateFiles/%s.%s.SeasonalFMerid.0",system->cName,body[iBody].cName);
    sprintf(cOutI,"SeasonalClimateFiles/%s.%s.SeasonalFIn.0",system->cName,body[iBody].cName);
    sprintf(cOutO,"SeasonalClimateFiles/%s.%s.SeasonalFOut.0",system->cName,body[iBody].cName);
    sprintf(cOutD,"SeasonalClimateFiles/%s.%s.SeasonalDivF.0",system->cName,body[iBody].cName);
  } else if (dTime < 10000) {
    sprintf(cOutM,"SeasonalClimateFiles/%s.%s.SeasonalFMerid.%.0f",system->cName,body[iBody].cName,dTime);
   sprintf(cOutI,"SeasonalClimateFiles/%s.%s.SeasonalFIn.%.0f",system->cName,body[iBody].cName,dTime);
   sprintf(cOutO,"SeasonalClimateFiles/%s.%s.SeasonalFOut.%.0f",system->cName,body[iBody].cName,dTime);
   sprintf(cOutD,"SeasonalClimateFiles/%s.%s.SeasonalDivF.%.0f",system->cName,body[iBody].cName,dTime);
  } else {
    sprintf(cOutM,"SeasonalClimateFiles/%s.%s.SeasonalFMerid.%.2e",system->cName,body[iBody].cName,dTime);
    sprintf(cOutI,"SeasonalClimateFiles/%s.%s.SeasonalFIn.%.2e",system->cName,body[iBody].cName,dTime);
    sprintf(cOutO,"SeasonalClimateFiles/%s.%s.SeasonalFOut.%.2e",system->cName,body[iBody].cName,dTime);
    sprintf(cOutD,"SeasonalClimateFiles/%s.%s.SeasonalDivF.%.2e",system->cName,body[iBody].cName,dTime);
  }

  fpM = fopen(cOutM,"w");
  fpI = fopen(cOutI,"w");
  fpO = fopen(cOutO,"w");
  fpD = fopen(cOutD,"w");

  for (iDay=0;iDay<body[iBody].iNumYears*body[iBody].iNStepInYear;iDay++) {
    for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
      //printf("%d %d\n",iLat,iDay);
      //printf("%d %d %lf\n",iLat,iDay,body[iBody].daTempDaily[iLat][iDay]);
      fprintd(fpM,body[iBody].daFluxDaily[iLat][iDay],control->Io.iSciNot,control->Io.iDigits);
      fprintf(fpM," ");

      fprintd(fpI,body[iBody].daFluxInDaily[iLat][iDay],control->Io.iSciNot,control->Io.iDigits);
      fprintf(fpI," ");

      fprintd(fpO,body[iBody].daFluxOutDaily[iLat][iDay],control->Io.iSciNot,control->Io.iDigits);
      fprintf(fpO," ");

      fprintd(fpD,body[iBody].daDivFluxDaily[iLat][iDay],control->Io.iSciNot,control->Io.iDigits);
      fprintf(fpD," ");
    }
    fprintf(fpM,"\n");
    fprintf(fpI,"\n");
    fprintf(fpO,"\n");
    fprintf(fpD,"\n");
  }
  fclose(fpM);
  fclose(fpI);
  fclose(fpO);
  fclose(fpD);
}

void WriteSeasonalIceBalance(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  char cOut[3*NAMELEN];
  FILE *fp;
  int iLat,iDay;

  double dTime;

  struct stat st = {0};
  if (stat("SeasonalClimateFiles",&st) == -1) {
#ifdef _WIN32
    mkdir("SeasonalClimateFiles");
#else
    mkdir("SeasonalClimateFiles",0700);
#endif
  }

  dTime = control->Evolve.dTime/fdUnitsTime(units->iTime);

  if (dTime == 0) {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.SeasonalIceBalance.0",system->cName,body[iBody].cName);
  } else if (dTime < 10000) {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.SeasonalIceBalance.%.0f",system->cName,body[iBody].cName,dTime);
  } else {
    sprintf(cOut,"SeasonalClimateFiles/%s.%s.SeasonalIceBalance.%.2e",system->cName,body[iBody].cName,dTime);
  }

  fp = fopen(cOut,"w");
  for (iDay=0;iDay<body[iBody].iNStepInYear;iDay++) {
    for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
      fprintd(fp,body[iBody].daIceBalance[iLat][iDay],control->Io.iSciNot,control->Io.iDigits);
      fprintf(fp," ");
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
}

void WriteFluxMerid(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daFlux[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daFluxAvg[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    *dTmp *= output->dNeg;
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergy(units->iTime,units->iMass,units->iLength);
    fsUnitsEnergy(units,cUnit);
  }
}

void WriteFluxIn(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daFluxIn[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daFluxInAvg[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime,units->iMass,units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteFluxOut(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daFluxOut[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daFluxOutAvg[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime,units->iMass,units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteDivFlux(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeas == 1) {
    *dTmp = body[iBody].daDivFlux[body[iBody].iWriteLat];
  } else if (body[iBody].bClimateModel == SEA) {
    *dTmp = body[iBody].daDivFluxAvg[body[iBody].iWriteLat];
  }

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime,units->iMass,units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteIceMass(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bIceSheets) {
    *dTmp = body[iBody].daIceMass[body[iBody].iWriteLat];
  } else {
    *dTmp = 0.0;
  }

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    //*dTmp /= fdUnitsMass(units->iMass)/pow(fdUnitsLength(units->iLength),2);
    //fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteIceHeight(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bIceSheets) {
    *dTmp = body[iBody].daIceMass[body[iBody].iWriteLat]/RHOICE;
  } else {
    *dTmp = 0.0;
  }

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsLength(units->iLength);
    fsUnitsLength(units->iLength,cUnit);
  }
}

void WriteBedrockH(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bIceSheets) {
    *dTmp = body[iBody].daBedrockH[body[iBody].iWriteLat];
  } else {
    *dTmp = 0.0;
  }

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsLength(units->iLength);
    fsUnitsLength(units->iLength,cUnit);
  }
}

void WritePlanckBAvg(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  if (body[iBody].bIceSheets) {
    *dTmp = body[iBody].daPlanckBAvg[body[iBody].iWriteLat];
  } else {
    *dTmp = 0.0;
  }

  // if (output->bDoNeg[iBody]) {
//     strcpy(cUnit,output->cNeg);
//   } else {
//     *dTmp /= fdUnitsLength(units->iLength);
//     fsUnitsLength(units->iLength,cUnit);
//   }
}

void WriteDIceMassDt(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  //*dTmp = body[iBody].daIceBalanceAnnual[body[iBody].iWriteLat];
  if (body[iBody].bIceSheets) {
    *dTmp = body[iBody].daIceBalanceAvg[body[iBody].iWriteLat]*RHOICE;
  } else {
    *dTmp = 0.0;
  }

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsLength(units->iLength);
    fsUnitsLength(units->iLength,cUnit);
  }
}

void WriteIceAccum(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  //*dTmp = body[iBody].daIceBalanceAnnual[body[iBody].iWriteLat];
  if (body[iBody].bIceSheets) {
    *dTmp = body[iBody].daIceAccumTot[body[iBody].iWriteLat]/RHOICE;
  } else {
    *dTmp = 0.0;
  }

  // if (output->bDoNeg[iBody]) {
//     strcpy(cUnit,output->cNeg);
//   } else {
//     *dTmp /= fdUnitsLength(units->iLength);
//     fsUnitsLength(units->iLength,cUnit);
//   }
}

void WriteIceAblate(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  //*dTmp = body[iBody].daIceBalanceAnnual[body[iBody].iWriteLat];
  if (body[iBody].bIceSheets) {
    *dTmp = body[iBody].daIceAblateTot[body[iBody].iWriteLat]/RHOICE;
  } else {
    *dTmp = 0.0;
  }

  // if (output->bDoNeg[iBody]) {
//     strcpy(cUnit,output->cNeg);
//   } else {
//     *dTmp /= fdUnitsLength(units->iLength);
//     fsUnitsLength(units->iLength,cUnit);
//   }
}


void WriteDIceMassDtFlow(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {
  // *dTmp = body[iBody].daIceBalanceAnnual[body[iBody].iWriteLat];
  if (body[iBody].bIceSheets) {
    *dTmp = body[iBody].daIceFlowAvg[body[iBody].iWriteLat];
  } else {
    *dTmp = 0.0;
  }

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    // *dTmp /= fdUnitsMass(units->iMass)/pow(fdUnitsLength(units->iLength),2);
    // fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteEnergyResL(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {

  *dTmp = body[iBody].daEnergyResL[body[iBody].iWriteLat];

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime,units->iMass,units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void WriteEnergyResW(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UNITS *units,UPDATE *update,int iBody,double *dTmp,char cUnit[]) {

  *dTmp = body[iBody].daEnergyResW[body[iBody].iWriteLat];

  if (output->bDoNeg[iBody]) {
    strcpy(cUnit,output->cNeg);
  } else {
    *dTmp /= fdUnitsEnergyFlux(units->iTime,units->iMass,units->iLength);
    fsUnitsEnergyFlux(units,cUnit);
  }
}

void InitializeOutputPoise(OUTPUT *output,fnWriteOutput fnWrite[]) {
  sprintf(output[OUT_TGLOBAL].cName,"TGlobal");
  sprintf(output[OUT_TGLOBAL].cDescr,"Global mean temperature from POISE");
  sprintf(output[OUT_TGLOBAL].cNeg,"C");
  output[OUT_TGLOBAL].bNeg = 1;
  output[OUT_TGLOBAL].dNeg = 1; //conversion is hardcoded in write function
  output[OUT_TGLOBAL].iNum = 1;
  output[OUT_TGLOBAL].iModuleBit = POISE;
  fnWrite[OUT_TGLOBAL] = &WriteTGlobal;

  sprintf(output[OUT_ALBEDOGLOBAL].cName,"AlbedoGlobal");
  sprintf(output[OUT_ALBEDOGLOBAL].cDescr,"Global mean bond albedo from POISE");
  output[OUT_ALBEDOGLOBAL].bNeg = 0;
  output[OUT_ALBEDOGLOBAL].iNum = 1;
  output[OUT_ALBEDOGLOBAL].iModuleBit = POISE;
  fnWrite[OUT_ALBEDOGLOBAL] = &WriteAlbedoGlobal;

  sprintf(output[OUT_SNOWBALL].cName,"Snowball");
  sprintf(output[OUT_SNOWBALL].cDescr,"Is the planet in a snowball state?");
  output[OUT_SNOWBALL].bNeg = 0;
  output[OUT_SNOWBALL].iNum = 1;
  output[OUT_SNOWBALL].iModuleBit = POISE;
  fnWrite[OUT_SNOWBALL] = &WriteSnowball;

  sprintf(output[OUT_TOTICEMASS].cName,"TotIceMass");
  sprintf(output[OUT_TOTICEMASS].cDescr,"Global total ice mass in ice sheets");
  sprintf(output[OUT_TOTICEMASS].cNeg,"kg");
  output[OUT_TOTICEMASS].bNeg = 1;
  output[OUT_TOTICEMASS].iNum = 1;
  output[OUT_TOTICEMASS].iModuleBit = POISE;
  fnWrite[OUT_TOTICEMASS] = &WriteTotIceMass;

  sprintf(output[OUT_TOTICEFLOW].cName,"TotIceFlow");
  sprintf(output[OUT_TOTICEFLOW].cDescr,"Global total ice flow in ice sheets (should = 0)");
  sprintf(output[OUT_TOTICEFLOW].cNeg,"kg");
  output[OUT_TOTICEFLOW].bNeg = 1;
  output[OUT_TOTICEFLOW].iNum = 1;
  output[OUT_TOTICEFLOW].iModuleBit = POISE;
  fnWrite[OUT_TOTICEFLOW] = &WriteIceFlowTot;

  sprintf(output[OUT_TOTICEBALANCE].cName,"TotIceBalance");
  sprintf(output[OUT_TOTICEBALANCE].cDescr,"Global total ice balance in ice sheets (this time step)");
  sprintf(output[OUT_TOTICEBALANCE].cNeg,"kg");
  output[OUT_TOTICEBALANCE].bNeg = 1;
  output[OUT_TOTICEBALANCE].iNum = 1;
  output[OUT_TOTICEBALANCE].iModuleBit = POISE;
  fnWrite[OUT_TOTICEBALANCE] = &WriteIceBalanceTot;

  sprintf(output[OUT_FLUXINGLOBAL].cName,"FluxInGlobal");
  sprintf(output[OUT_FLUXINGLOBAL].cDescr,"Global mean flux in (insol*(1-albedo)) from POISE");
  /* Sadly, Russell, we must set the negative option to W/m^2.
  sprintf(output[OUT_FLUXINGLOBAL].cNeg,"pirate-ninjas/m^2");
  output[OUT_FLUXINGLOBAL].dNeg = 1/40.55185;
  */
  output[OUT_FLUXINGLOBAL].bNeg = 1;
  output[OUT_FLUXINGLOBAL].dNeg = 1; // Just in case
  sprintf(output[OUT_FLUXINGLOBAL].cNeg,"W/m^2");
  output[OUT_FLUXINGLOBAL].iNum = 1;
  output[OUT_FLUXINGLOBAL].iModuleBit = POISE;
  fnWrite[OUT_FLUXINGLOBAL] = &WriteFluxInGlobal;

  sprintf(output[OUT_FLUXOUTGLOBAL].cName,"FluxOutGlobal");
  sprintf(output[OUT_FLUXOUTGLOBAL].cDescr,"Global mean flux out from POISE");
  /* Here, too
  sprintf(output[OUT_FLUXOUTGLOBAL].cNeg,"pirate-ninjas/m^2");
  output[OUT_FLUXOUTGLOBAL].dNeg = 1/40.55185;
  */
  output[OUT_FLUXOUTGLOBAL].bNeg = 1;
  output[OUT_FLUXOUTGLOBAL].dNeg = 1;
  sprintf(output[OUT_FLUXOUTGLOBAL].cNeg,"W/m^2");
  output[OUT_FLUXOUTGLOBAL].iNum = 1;
  output[OUT_FLUXOUTGLOBAL].iModuleBit = POISE;
  fnWrite[OUT_FLUXOUTGLOBAL] = &WriteFluxOutGlobal;

  sprintf(output[OUT_TEMPLAT].cName,"TempLat");
  sprintf(output[OUT_TEMPLAT].cDescr,"Surface temperature by latitude.");
  sprintf(output[OUT_TEMPLAT].cNeg,"C");
  output[OUT_TEMPLAT].bNeg = 1;
  output[OUT_TEMPLAT].dNeg = 1; //conversion is hardcoded in write function
  output[OUT_TEMPLAT].iNum = 1;
  output[OUT_TEMPLAT].bGrid = 1;
  output[OUT_TEMPLAT].iModuleBit = POISE;
  fnWrite[OUT_TEMPLAT] = &WriteTempLat;

  sprintf(output[OUT_TEMPMINLAT].cName,"TempMinLat");
  sprintf(output[OUT_TEMPMINLAT].cDescr,"Minimum surface temperature over a year by latitude.");
  sprintf(output[OUT_TEMPMINLAT].cNeg,"C");
  output[OUT_TEMPMINLAT].bNeg = 1;
  output[OUT_TEMPMINLAT].dNeg = 1; //conversion is hardcoded in write function
  output[OUT_TEMPMINLAT].iNum = 1;
  output[OUT_TEMPMINLAT].bGrid = 1;
  output[OUT_TEMPMINLAT].iModuleBit = POISE;
  fnWrite[OUT_TEMPMINLAT] = &WriteTempMinLat;

  sprintf(output[OUT_TEMPMAXLAT].cName,"TempMaxLat");
  sprintf(output[OUT_TEMPMAXLAT].cDescr,"Maximum surface temperature over a year by latitude.");
  sprintf(output[OUT_TEMPMAXLAT].cNeg,"C");
  output[OUT_TEMPMAXLAT].bNeg = 1;
  output[OUT_TEMPMAXLAT].dNeg = 1; //conversion is hardcoded in write function
  output[OUT_TEMPMAXLAT].iNum = 1;
  output[OUT_TEMPMAXLAT].bGrid = 1;
  output[OUT_TEMPMAXLAT].iModuleBit = POISE;
  fnWrite[OUT_TEMPMAXLAT] = &WriteTempMaxLat;

  sprintf(output[OUT_TEMPMAXLAND].cName,"TempMaxLand");
  sprintf(output[OUT_TEMPMAXLAND].cDescr,"Maximum surface temperature on land");
  sprintf(output[OUT_TEMPMAXLAND].cNeg,"C");
  output[OUT_TEMPMAXLAND].bNeg = 1;
  output[OUT_TEMPMAXLAND].dNeg = 1; //conversion is hardcoded in write function
  output[OUT_TEMPMAXLAND].iNum = 1;
  output[OUT_TEMPMAXLAND].bGrid = 1;
  output[OUT_TEMPMAXLAND].iModuleBit = POISE;
  fnWrite[OUT_TEMPMAXLAND] = &WriteTempMaxLand;

  sprintf(output[OUT_TEMPMAXWATER].cName,"TempMaxWater");
  sprintf(output[OUT_TEMPMAXWATER].cDescr,"Maximum surface temperature on water");
  sprintf(output[OUT_TEMPMAXWATER].cNeg,"C");
  output[OUT_TEMPMAXWATER].bNeg = 1;
  output[OUT_TEMPMAXWATER].dNeg = 1; //conversion is hardcoded in write function
  output[OUT_TEMPMAXWATER].iNum = 1;
  output[OUT_TEMPMAXWATER].bGrid = 1;
  output[OUT_TEMPMAXWATER].iModuleBit = POISE;
  fnWrite[OUT_TEMPMAXWATER] = &WriteTempMaxWater;

  sprintf(output[OUT_TEMPLANDLAT].cName,"TempLandLat");
  sprintf(output[OUT_TEMPLANDLAT].cDescr,"Land surface temperature by latitude.");
  sprintf(output[OUT_TEMPLANDLAT].cNeg,"C");
  output[OUT_TEMPLANDLAT].bNeg = 1;
  output[OUT_TEMPLANDLAT].dNeg = 1; //conversion is hardcoded in write function
  output[OUT_TEMPLANDLAT].iNum = 1;
  output[OUT_TEMPLANDLAT].bGrid = 1;
  fnWrite[OUT_TEMPLANDLAT] = &WriteTempLandLat;

  sprintf(output[OUT_TEMPWATERLAT].cName,"TempWaterLat");
  sprintf(output[OUT_TEMPWATERLAT].cDescr,"Water surface temperature by latitude.");
  sprintf(output[OUT_TEMPWATERLAT].cNeg,"C");
  output[OUT_TEMPWATERLAT].bNeg = 1;
  output[OUT_TEMPWATERLAT].dNeg = 1; //conversion is hardcoded in write function
  output[OUT_TEMPWATERLAT].iNum = 1;
  output[OUT_TEMPWATERLAT].bGrid = 1;
  fnWrite[OUT_TEMPWATERLAT] = &WriteTempWaterLat;

  sprintf(output[OUT_LATITUDE].cName,"Latitude");
  sprintf(output[OUT_LATITUDE].cDescr,"Latitude.");
  sprintf(output[OUT_LATITUDE].cNeg,"Degrees");
  output[OUT_LATITUDE].bNeg = 1;
  output[OUT_LATITUDE].dNeg = 1/DEGRAD;
  output[OUT_LATITUDE].iNum = 1;
  output[OUT_LATITUDE].bGrid = 1;
  output[OUT_LATITUDE].iModuleBit = POISE;
  fnWrite[OUT_LATITUDE] = &WriteLatitude;

  sprintf(output[OUT_ALBEDOLAT].cName,"AlbedoLat");
  sprintf(output[OUT_ALBEDOLAT].cDescr,"Surface albedo by latitude.");
  output[OUT_ALBEDOLAT].bNeg = 0;
  output[OUT_ALBEDOLAT].iNum = 1;
  output[OUT_ALBEDOLAT].bGrid = 1;
  output[OUT_ALBEDOLAT].iModuleBit = POISE;
  fnWrite[OUT_ALBEDOLAT] = &WriteAlbedoLat;

  sprintf(output[OUT_ALBEDOLANDLAT].cName,"AlbedoLandLat");
  sprintf(output[OUT_ALBEDOLANDLAT].cDescr,"Land surface albedo by latitude.");
  output[OUT_ALBEDOLANDLAT].bNeg = 0;
  output[OUT_ALBEDOLANDLAT].iNum = 1;
  output[OUT_ALBEDOLANDLAT].bGrid = 1;
  fnWrite[OUT_ALBEDOLANDLAT] = &WriteAlbedoLandLat;

  sprintf(output[OUT_ALBEDOWATERLAT].cName,"AlbedoWaterLat");
  sprintf(output[OUT_ALBEDOWATERLAT].cDescr,"Water surface albedo by latitude.");
  output[OUT_ALBEDOWATERLAT].bNeg = 0;
  output[OUT_ALBEDOWATERLAT].iNum = 1;
  output[OUT_ALBEDOWATERLAT].bGrid = 1;
  fnWrite[OUT_ALBEDOWATERLAT] = &WriteAlbedoWaterLat;

  sprintf(output[OUT_ANNUALINSOL].cName,"AnnInsol");
  sprintf(output[OUT_ANNUALINSOL].cDescr,"Annual insolation by latitude.");
  sprintf(output[OUT_ANNUALINSOL].cNeg,"W/m^2");
  output[OUT_ANNUALINSOL].bNeg = 1;
  output[OUT_ANNUALINSOL].dNeg = 1/40.55185;
  output[OUT_ANNUALINSOL].iNum = 1;
  output[OUT_ANNUALINSOL].bGrid = 1;
  output[OUT_ANNUALINSOL].iModuleBit = POISE;
  fnWrite[OUT_ANNUALINSOL] = &WriteAnnualInsol;

  sprintf(output[OUT_PEAKINSOL].cName,"PeakInsol");
  sprintf(output[OUT_PEAKINSOL].cDescr,"Peak insolation by latitude.");
  sprintf(output[OUT_PEAKINSOL].cNeg,"W/m^2");
  output[OUT_PEAKINSOL].bNeg = 1;
  output[OUT_PEAKINSOL].dNeg = 1/40.55185;
  output[OUT_PEAKINSOL].iNum = 1;
  output[OUT_PEAKINSOL].bGrid = 1;
  output[OUT_PEAKINSOL].iModuleBit = POISE;
  fnWrite[OUT_PEAKINSOL] = &WritePeakInsol;

  sprintf(output[OUT_FLUXMERID].cName,"FluxMerid");
  sprintf(output[OUT_FLUXMERID].cDescr,"Total meridional (northward) flux by latitude");
  sprintf(output[OUT_FLUXMERID].cNeg,"PW");
  output[OUT_FLUXMERID].bNeg = 1;
  output[OUT_FLUXMERID].dNeg = 1e-15;
  output[OUT_FLUXMERID].iNum = 1;
  output[OUT_FLUXMERID].bGrid = 1;
  output[OUT_FLUXMERID].iModuleBit = POISE;
  fnWrite[OUT_FLUXMERID] = &WriteFluxMerid;

  sprintf(output[OUT_FLUXIN].cName,"FluxIn");
  sprintf(output[OUT_FLUXIN].cDescr,"Incoming flux by latitude");
  sprintf(output[OUT_FLUXIN].cNeg,"W/m^2");
  output[OUT_FLUXIN].bNeg = 1;
  output[OUT_FLUXIN].dNeg = 1;
  output[OUT_FLUXIN].iNum = 1;
  output[OUT_FLUXIN].bGrid = 1;
  output[OUT_FLUXIN].iModuleBit = POISE;
  fnWrite[OUT_FLUXIN] = &WriteFluxIn;

  sprintf(output[OUT_FLUXOUT].cName,"FluxOut");
  sprintf(output[OUT_FLUXOUT].cDescr,"Outgoing (spaceward) flux by latitude");
  sprintf(output[OUT_FLUXOUT].cNeg,"W/m^2");
  output[OUT_FLUXOUT].bNeg = 1;
  output[OUT_FLUXOUT].dNeg = 1;
  output[OUT_FLUXOUT].iNum = 1;
  output[OUT_FLUXOUT].bGrid = 1;
  output[OUT_FLUXOUT].iModuleBit = POISE;
  fnWrite[OUT_FLUXOUT] = &WriteFluxOut;

  sprintf(output[OUT_DIVFLUX].cName,"DivFlux");
  sprintf(output[OUT_DIVFLUX].cDescr,"Divergence of flux (flow into adjacent cells) by latitude");
  sprintf(output[OUT_DIVFLUX].cNeg,"W/m^2");
  output[OUT_DIVFLUX].bNeg = 1;
  output[OUT_DIVFLUX].dNeg = 1;
  output[OUT_DIVFLUX].iNum = 1;
  output[OUT_DIVFLUX].bGrid = 1;
  output[OUT_DIVFLUX].iModuleBit = POISE;
  fnWrite[OUT_DIVFLUX] = &WriteDivFlux;

  sprintf(output[OUT_ICEMASS].cName,"IceMass");
  sprintf(output[OUT_ICEMASS].cDescr,"Mass of ice sheets/area by latitude");
  sprintf(output[OUT_ICEMASS].cNeg,"kg/m^2");
  output[OUT_ICEMASS].bNeg = 1;
  output[OUT_ICEMASS].dNeg = 1;
  output[OUT_ICEMASS].iNum = 1;
  output[OUT_ICEMASS].bGrid = 1;
  output[OUT_ICEMASS].iModuleBit = POISE;
  fnWrite[OUT_ICEMASS] = &WriteIceMass;

  sprintf(output[OUT_ICEHEIGHT].cName,"IceHeight");
  sprintf(output[OUT_ICEHEIGHT].cDescr,"Height of ice sheets");
  sprintf(output[OUT_ICEHEIGHT].cNeg,"m");
  output[OUT_ICEHEIGHT].bNeg = 1;
  output[OUT_ICEHEIGHT].dNeg = 1;
  output[OUT_ICEHEIGHT].iNum = 1;
  output[OUT_ICEHEIGHT].bGrid = 1;
  output[OUT_ICEHEIGHT].iModuleBit = POISE;
  fnWrite[OUT_ICEHEIGHT] = &WriteIceHeight;

  sprintf(output[OUT_DICEMASSDT].cName,"DIceMassDt");
  sprintf(output[OUT_DICEMASSDT].cDescr,"derivative of mass of ice sheets/area by latitude");
  sprintf(output[OUT_DICEMASSDT].cNeg,"kg/m^2/s");
  output[OUT_DICEMASSDT].bNeg = 1;
  output[OUT_DICEMASSDT].dNeg = 1;
  output[OUT_DICEMASSDT].iNum = 1;
  output[OUT_DICEMASSDT].bGrid = 1;
  output[OUT_DICEMASSDT].iModuleBit = POISE;
  fnWrite[OUT_DICEMASSDT] = &WriteDIceMassDt;

  sprintf(output[OUT_ICEACCUM].cName,"IceAccum");
  sprintf(output[OUT_ICEACCUM].cDescr,"ice growth per orbit (accumulation only)");
  sprintf(output[OUT_ICEACCUM].cNeg,"m/orbit");
  output[OUT_ICEACCUM].bNeg = 1;
  output[OUT_ICEACCUM].dNeg = 1;
  output[OUT_ICEACCUM].iNum = 1;
  output[OUT_ICEACCUM].bGrid = 1;
  output[OUT_ICEACCUM].iModuleBit = POISE;
  fnWrite[OUT_ICEACCUM] = &WriteIceAccum;

  sprintf(output[OUT_ICEABLATE].cName,"IceAblate");
  sprintf(output[OUT_ICEABLATE].cDescr,"ice decay per orbit (ablation only)");
  sprintf(output[OUT_ICEABLATE].cNeg,"m/orbit");
  output[OUT_ICEABLATE].bNeg = 1;
  output[OUT_ICEABLATE].dNeg = 1;
  output[OUT_ICEABLATE].iNum = 1;
  output[OUT_ICEABLATE].bGrid = 1;
  output[OUT_ICEABLATE].iModuleBit = POISE;
  fnWrite[OUT_ICEABLATE] = &WriteIceAblate;

  sprintf(output[OUT_ICEFLOW].cName,"IceFlow");
  sprintf(output[OUT_ICEFLOW].cDescr,"flow of ice sheets/area by latitude");
  sprintf(output[OUT_ICEFLOW].cNeg,"m/s");
  output[OUT_ICEFLOW].bNeg = 1;
  output[OUT_ICEFLOW].dNeg = 1;
  output[OUT_ICEFLOW].iNum = 1;
  output[OUT_ICEFLOW].bGrid = 1;
  output[OUT_ICEFLOW].iModuleBit = POISE;
  fnWrite[OUT_ICEFLOW] = &WriteDIceMassDtFlow;

  sprintf(output[OUT_BEDROCKH].cName,"BedrockH");
  sprintf(output[OUT_BEDROCKH].cDescr,"height/depth of bedrock");
  sprintf(output[OUT_BEDROCKH].cNeg,"m");
  output[OUT_BEDROCKH].bNeg = 1;
  output[OUT_BEDROCKH].dNeg = 1;
  output[OUT_BEDROCKH].iNum = 1;
  output[OUT_BEDROCKH].bGrid = 1;
  output[OUT_BEDROCKH].iModuleBit = POISE;
  fnWrite[OUT_BEDROCKH] = &WriteBedrockH;

  sprintf(output[OUT_ENERGYRESL].cName,"EnergyResL");
  sprintf(output[OUT_ENERGYRESL].cDescr,"Energy residual on land");
  sprintf(output[OUT_ENERGYRESL].cNeg,"W/m^2");
  output[OUT_ENERGYRESL].bNeg = 1;
  output[OUT_ENERGYRESL].dNeg = 1;
  output[OUT_ENERGYRESL].iNum = 1;
  output[OUT_ENERGYRESL].bGrid = 1;
  output[OUT_ENERGYRESL].iModuleBit = POISE;
  fnWrite[OUT_ENERGYRESL] = &WriteEnergyResL;

  sprintf(output[OUT_ENERGYRESW].cName,"EnergyResW");
  sprintf(output[OUT_ENERGYRESW].cDescr,"Energy residual over water");
  sprintf(output[OUT_ENERGYRESW].cNeg,"W/m^2");
  output[OUT_ENERGYRESW].bNeg = 1;
  output[OUT_ENERGYRESW].dNeg = 1;
  output[OUT_ENERGYRESW].iNum = 1;
  output[OUT_ENERGYRESW].bGrid = 1;
  output[OUT_ENERGYRESW].iModuleBit = POISE;
  fnWrite[OUT_ENERGYRESW] = &WriteEnergyResW;

  sprintf(output[OUT_SKIPSEAS].cName,"SkipSeas");
  sprintf(output[OUT_SKIPSEAS].cDescr,"Is Seasonal model skipped due to RGH or snowball?");
  output[OUT_SKIPSEAS].bNeg = 0;
  output[OUT_SKIPSEAS].iNum = 1;
  output[OUT_SKIPSEAS].iModuleBit = POISE;
  fnWrite[OUT_SKIPSEAS] = &WriteSkipSeas;

  sprintf(output[OUT_PLANCKBAVG].cName,"PlanckBAvg");
  sprintf(output[OUT_PLANCKBAVG].cDescr,"Annually averaged Planck B coeff");
  sprintf(output[OUT_PLANCKBAVG].cNeg,"W/m^2/C");
  output[OUT_PLANCKBAVG].bNeg = 0;
  output[OUT_PLANCKBAVG].iNum = 1;
  output[OUT_PLANCKBAVG].bGrid = 1;
  output[OUT_PLANCKBAVG].iModuleBit = POISE;
  fnWrite[OUT_PLANCKBAVG] = &WritePlanckBAvg;

  sprintf(output[OUT_AREAICECOV].cName,"AreaIceCov");
  sprintf(output[OUT_AREAICECOV].cDescr,"Fractional area ice covered");
  sprintf(output[OUT_AREAICECOV].cNeg," ");
  output[OUT_AREAICECOV].bNeg = 1;
  output[OUT_AREAICECOV].iNum = 1;
  output[OUT_AREAICECOV].iModuleBit = POISE;
  fnWrite[OUT_AREAICECOV] = &WriteAreaIceCov;
}

/************ POISE Logging Functions **************/

void LogOptionsPoise(CONTROL *control, FILE *fp) {
  fprintf(fp,"-------- POISE Options -----\n\n");
}

void LogPoise(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UPDATE *update,fnWriteOutput fnWrite[],FILE *fp) {
  int iOut;

  fprintf(fp,"\n----- POISE PARAMETERS ------\n");
  for (iOut=OUTSTARTPOISE;iOut<OUTBODYSTARTPOISE;iOut++) {
    if (output[iOut].iNum > 0)
      WriteLogEntry(body,control,&output[iOut],system,update,fnWrite[iOut],fp,0);
  }
}

void LogBodyPoise(BODY *body,CONTROL *control,OUTPUT *output,SYSTEM *system,UPDATE *update,fnWriteOutput fnWrite[],FILE *fp,int iBody) {
  int iOut;

  fprintf(fp,"-----POISE PARAMETERS (%s)------\n",body[iBody].cName);
  for (iOut=OUTBODYSTARTPOISE;iOut<OUTENDPOISE;iOut++) {
    if (output[iOut].iNum > 0)
      WriteLogEntry(body,control,&output[iOut],system,update,fnWrite[iOut],fp,iBody);
  }
}

/************* MODULE Functions ***********/

void AddModulePoise(CONTROL *control,MODULE *module,int iBody,int iModule) {

  module->iaModule[iBody][iModule]                  = POISE;

  module->fnInitializeUpdateTmpBody[iBody][iModule] = &InitializeUpdateTmpBodyPoise;
  module->fnCountHalts[iBody][iModule]              = &CountHaltsPoise;
  module->fnLogBody[iBody][iModule]                 = &LogBodyPoise;

  module->fnReadOptions[iBody][iModule]             = &ReadOptionsPoise;
  module->fnVerify[iBody][iModule]                  = &VerifyPoise;
  module->fnAssignDerivatives[iBody][iModule]       = &AssignPoiseDerivatives;
  module->fnNullDerivatives[iBody][iModule]         = &NullPoiseDerivatives;
  module->fnVerifyHalt[iBody][iModule]              = &VerifyHaltPoise;

  module->fnInitializeUpdate[iBody][iModule]        = &InitializeUpdatePoise;
  module->fnInitializeOutput[iBody][iModule]        = &InitializeOutputPoise;
}

/************* POISE Functions ***********/

void UpdateOrbitOblData(BODY *body, EVOLVE *evolve, int iBody) {
  body[iBody].dSemi = body[iBody].daSemiSeries[body[iBody].iCurrentStep];
  body[iBody].dEcc = body[iBody].daEccSeries[body[iBody].iCurrentStep];
  body[iBody].dArgP = body[iBody].daArgPSeries[body[iBody].iCurrentStep];
  body[iBody].dLongA = body[iBody].daLongASeries[body[iBody].iCurrentStep];
  body[iBody].dObliquity = body[iBody].daOblSeries[body[iBody].iCurrentStep];
  body[iBody].dPrecA = body[iBody].daPrecASeries[body[iBody].iCurrentStep];
  
  body[iBody].dXobl = sin(body[iBody].dObliquity)*cos(body[iBody].dPrecA);
  body[iBody].dYobl = sin(body[iBody].dObliquity)*sin(body[iBody].dPrecA);
  body[iBody].dZobl = cos(body[iBody].dObliquity);
  
  body[iBody].dHecc = body[iBody].daHeccSeries[body[iBody].iCurrentStep];
  body[iBody].dKecc = body[iBody].daKeccSeries[body[iBody].iCurrentStep];
}

/**
Calculates flow at base of ice sheet

@param body Struct containing all body information and variables
@param iBody Body in question
@param iLat Index of current latitude cell
@return Flow rate at base of ice sheet (velocity*height -> m^2/s)
*/
double BasalFlow(BODY *body, int iBody, int iLat){
  double ased, bsed, dTmp, m = 1.25, minv, grav;

  if (body[iBody].daSedShear[iLat] == 0) {
    return 0.0;
  } else {
    ased = body[iBody].daSedShear[iLat];
    grav = BIGG*body[iBody].dMass/(body[iBody].dRadius*body[iBody].dRadius);
    bsed = (RHOSED - RHOH2O)*grav*tan(SEDPHI);

    if (fabs(ased)/bsed <= SEDH) {
      minv = 0;
    } else {
      minv = 1 - bsed/fabs(ased)*SEDH;
    }

    dTmp = 2*(SEDD0*RHOICE*grav*(body[iBody].daIceHeight[iLat]\
        *body[iBody].daIceHeight[iLat]))/((m+1)*bsed)*\
        pow(fabs(ased)/(2*SEDD0*SEDMU),m) * (1.0-pow(minv,m+1));

    return dTmp;
  }
}

/**
Determines if planet has entered snowball state

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void Snowball(BODY *body, int iBody) {
  int iLat, iNum=0;

  for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
    if (body[iBody].bSeaIceModel) {
      if (body[iBody].daSeaIceHeight[iLat] > 0) {
        iNum++;
      }
    } else {
      if (body[iBody].daTempMaxWater[iLat] <= body[iBody].dFrzTSeaIce) {
        iNum++;
      }
    }
  }
  if (iNum == body[iBody].iNumLats) {
    body[iBody].bSnowball = 1;
  } else {
    body[iBody].bSnowball = 0;
  }
}

/**
Standard properties function for POISE. Updates auxiliary quantities
(currently just the dynamical ellipticity when DistRot is not enabled).

@param body Struct containing all body information and variables
@param evolve Struct containing evolve information and variables
@param update Struct containing update information and variables
@param iBody Body in question
*/
void PropsAuxPoise(BODY *body,EVOLVE *evolve,IO *io,UPDATE *update,int iBody) {
  if (body[iBody].bEqtide && body[iBody].bCalcDynEllip) {
    if (body[iBody].bDistRot == 0) {
      body[iBody].dDynEllip = CalcDynEllipEq(body, iBody);
    }
  }

}

/**
Calculates precession of the spin axis when DistRot is disabled

@param body Struct containing all body information and variables
@param evolve Struct containing evolve information and variables
@param iBody Body in question
*/
void PrecessionExplicit(BODY *body,EVOLVE *evolve,int iBody) {
  /* calculates precession angle as an explicit function of time
     for use only when distrot is not called! */
  double ecc2;
  ecc2 = body[iBody].dHecc*body[iBody].dHecc + body[iBody].dKecc*body[iBody].dKecc;
  body[iBody].dPrecA = 3.*BIGG*body[0].dMass/(2.*(body[iBody].dSemi*body[iBody].dSemi*body[iBody].dSemi)*body[iBody].dRotRate) *\
                       body[iBody].dDynEllip*pow((1.0-ecc2),-3./2)*cos(body[iBody].dObliquity) * \
                       evolve->dTime + body[iBody].dPrecA0;
  while (body[iBody].dPrecA >= 2*PI) body[iBody].dPrecA -= 2*PI;
  while (body[iBody].dPrecA < 0) body[iBody].dPrecA += 2*PI;
}

/**
Forces obliquity oscillation (bForceObliq = 1).

@param body Struct containing all body information and variables
@param evolve Struct containing evolve information and variables
@param iBody Body in question
*/
void ForceObliq(BODY *body, EVOLVE  *evolve, int iBody) {
  double A, P, C;
  P = body[iBody].dObliqPer*YEARSEC;
  A = body[iBody].dObliqAmp;
  C = body[iBody].dObliq0;

  body[iBody].dObliquity = (0.5*A*sin(2*PI*evolve->dTime/P))*DEGRAD+C;
  CalcXYZobl(body,iBody);
}

/**
Forces eccentricity oscillation (bForceEcc = 1).

@param body Struct containing all body information and variables
@param evolve Struct containing evolve information and variables
@param iBody Body in question
*/
void ForceEcc(BODY *body, EVOLVE  *evolve, int iBody) {
  double A, P, C;
  P = body[iBody].dEccPer*YEARSEC;
  A = body[iBody].dEccAmp;
  C = body[iBody].dEcc0;

  body[iBody].dEcc = (A*sin(2*PI*evolve->dTime/P))+C;
  CalcHK(body,iBody);
}

/**
Calculates the fractional ice covered area of the planet

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void AreaIceCovered(BODY *body, int iBody) {
//area permanently ice covered (i.e., all year round)

  int iLat;

  body[iBody].dAreaIceCov = 0;
  for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
    if (body[iBody].bClimateModel == SEA) {
      if (body[iBody].daIceMass[iLat] > 0 || body[iBody].daTempMaxLand[iLat] <= -2.0) {
        body[iBody].dAreaIceCov += body[iBody].daLandFrac[iLat];
      }
    } else {
      if (body[iBody].daTempMaxLand[iLat] <= -10.0) {
        body[iBody].dAreaIceCov += body[iBody].daLandFrac[iLat];
      }
    }
    if (body[iBody].daTempMaxWater[iLat] < -2) {
      body[iBody].dAreaIceCov += body[iBody].daWaterFrac[iLat];
    }
  }
  body[iBody].dAreaIceCov /= body[iBody].iNumLats;
}

/**
Force behavior function for POISE. This is where the magic happens--
POISE works entirely in force behavior because it needs to solve several
PDEs (not well modeled with RK4). First, the EBM (climate) is run for several
orbits, then the ice sheet flow. The EBM can be periodically rerun needed.

@param body Struct containing all body information and variables
@param module Struct containing module/intermodule quantities
@param evolve Struct containing evolve information and variables
@param io Struct containing read/write information
@param system Struct containing system-wide information
@param update Struct containing update information and variables
@param fnUpdate Array of function pointers to derivatives
@param iBody Body in question
@param iModule Module in question
*/
void ForceBehaviorPoise(BODY *body,MODULE *module,EVOLVE *evolve,IO *io,SYSTEM *system,UPDATE *update,fnUpdateVariable ***fnUpdate,int iBody,int iModule) {
  int iLat;

  // XXX Conflicts here. And there should be no reference to pizza in POISE

  if (body[iBody].bEqtide) {
    body[iBody].dMeanMotion = \
          fdSemiToMeanMotion(body[iBody].dSemi,body[0].dMass+body[iBody].dMass);
    body[iBody].iNDays = (int)floor(body[iBody].dRotRate/body[iBody].dMeanMotion);
    if (body[iBody].bClimateModel == SEA) {
      VerifyNStepSeasonal(body,iBody);
    }
  }

  if (body[iBody].bDistRot == 0) {
    PrecessionExplicit(body,evolve,iBody);
    if (body[iBody].bForceObliq) {
      ForceObliq(body,evolve,iBody);
    }
    if (body[iBody].bForceEcc) {
      ForceEcc(body,evolve,iBody);
    }
    if (body[iBody].bReadOrbitOblData) {
      UpdateOrbitOblData(body,evolve,iBody);
      body[iBody].iCurrentStep++;
    }

  }
  

  if (body[iBody].bClimateModel == ANN || body[iBody].bSkipSeasEnabled) {
    if (body[iBody].bClimateModel == SEA) {
      body[iBody].dSurfAlbedo = (body[iBody].dAlbedoLand + body[iBody].dAlbedoWater)/2.0;
    }

    PoiseAnnual(body,iBody);
  }

  if (body[iBody].bClimateModel == SEA) {
    if (body[iBody].bSkipSeas == 0) {
      body[iBody].dIceBalanceTot = 0.0;  //total change in ice mass this time step
      body[iBody].dIceFlowTot = 0.0;  //total ice flow (should equal zero)
      body[iBody].dIceMassTot = 0.0;
      if (body[iBody].bIceSheets) {
        PoiseIceSheets(body,evolve,iBody);
      }
    }

    if (body[iBody].bSkipSeasEnabled) {
      if (body[iBody].dFluxOutGlobal >= 300 || body[iBody].dAlbedoGlobal >= body[iBody].dIceAlbedo) {
        body[iBody].bSkipSeas = 1;
      } else {
        body[iBody].bSkipSeas = 0;
      }
    }

    if (body[iBody].bSkipSeas == 0) {
      AnnualInsolation(body,iBody);
      MatrixSeasonal(body,iBody);
      PoiseSeasonal(body,iBody);
    }
  }

  if (body[iBody].bSkipSeas == 0) {
    if (body[iBody].bIceSheets) {
      for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
        if (body[iBody].daIceMass[iLat] < 0) {
          body[iBody].daIceMass[iLat] = 0.0;
        }
        if (body[iBody].bClimateModel == SEA) {
          body[iBody].dIceMassTot += body[iBody].daIceMass[iLat]*(2*PI*(body[iBody].dRadius*body[iBody].dRadius)*(sin(body[iBody].daLats[1])-sin(body[iBody].daLats[0])))*body[iBody].daLandFrac[iLat];
          body[iBody].dIceBalanceTot += body[iBody].daIceBalanceAvg[iLat];
          body[iBody].dIceFlowTot += body[iBody].daIceFlowAvg[iLat];
        }
      }
    }
  }
}


/**
Calculates eccentric anomaly from true anomaly

@param TrueA Planet's true anomaly
@param Ecc Planet's orbital eccentricity
@return Eccentric anomaly
*/
double true2eccA(double TrueA, double Ecc) {
  double cosE;
  cosE = (cos(TrueA) + Ecc) / (1.0 + Ecc*cos(TrueA));

  if (TrueA < PI) {
    return acos(cosE);
  } else {
    return (2*PI - acos(cosE));
  }
}

/**
Calculates insolation at each latitude for a single "day" of the year/orbit

@param body Struct containing all body information and variables
@param iBody Body in question
@param iDay Day of the year
*/
void DailyInsolation(BODY *body, int iBody, int iDay) {
  int j;
  double Sconst, sin_delta, cos_delta, tan_delta, delta, HA;

  Sconst = body[0].dLuminosity / (4.*PI*(body[iBody].dSemi*body[iBody].dSemi));

  sin_delta = sin(body[iBody].dObliquity)*sin(body[iBody].dTrueL);
  cos_delta = sqrt(1.0-(sin_delta*sin_delta));
  tan_delta = sin_delta/cos_delta;
  delta = asin(sin_delta);
  body[iBody].daDeclination[iDay] = delta;

  for (j=0;j<body[iBody].iNumLats;j++) {
    if (delta > 0.0) {
      /* Northern summer */
      if (body[iBody].daLats[j] >= (PI/2.-delta)) {
        /* white night/no sunset */
        body[iBody].daInsol[j][iDay] = Sconst*sin(body[iBody].daLats[j])*sin_delta/(body[iBody].dAstroDist*body[iBody].dAstroDist);
      } else if (-body[iBody].daLats[j] >= (PI/2.-delta) && body[iBody].daLats[j] < 0.0) {
        /* polar darkness/no sunrise */
        body[iBody].daInsol[j][iDay] = 0.0;
      } else {
        /* regular day/night cycle */
        HA = acos(-tan(body[iBody].daLats[j])*tan_delta);
        body[iBody].daInsol[j][iDay] = Sconst * (HA*sin(body[iBody].daLats[j])*sin_delta + \
            cos(body[iBody].daLats[j])*cos_delta*sin(HA)) / (PI*(body[iBody].dAstroDist*body[iBody].dAstroDist));
      }
    } else {
      /* Southern summer */
      if (-body[iBody].daLats[j] >= (PI/2.+delta) && body[iBody].daLats[j] < 0.0) {
        /* white night/no sunset */
        body[iBody].daInsol[j][iDay] = Sconst*sin(body[iBody].daLats[j])*sin_delta/(body[iBody].dAstroDist*body[iBody].dAstroDist);
      } else if (body[iBody].daLats[j] >= (PI/2.+delta)) {
        /* polar darkness/no sunrise */
        body[iBody].daInsol[j][iDay] = 0.0;
      } else {
        /* regular day/night cycle */
        HA = acos(-tan(body[iBody].daLats[j])*tan_delta);
        body[iBody].daInsol[j][iDay] = Sconst * (HA*sin(body[iBody].daLats[j])*sin_delta + \
            cos(body[iBody].daLats[j])*cos_delta*sin(HA)) / (PI*(body[iBody].dAstroDist*body[iBody].dAstroDist));
      }
    }
  }
}

/**
Calculates insolation at each latitude over the entire year/orbit

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void AnnualInsolation(BODY *body, int iBody) {
  int i, j;
  double LongP, TrueA, EccA, MeanL, Ecc;

  LongP = body[iBody].dLongP+body[iBody].dPrecA+ PI; //Pericenter, relative to direction of planet at spring equinox
  Ecc = sqrt(body[iBody].dHecc*body[iBody].dHecc+body[iBody].dKecc*body[iBody].dKecc);

  body[iBody].dTrueL = -PI/2;        //starts the year at the (northern) winter solstice
  TrueA = body[iBody].dTrueL - LongP;
  while (TrueA < 0.0) TrueA += 2*PI;
  body[iBody].dObliquity = atan2(sqrt((body[iBody].dXobl*body[iBody].dXobl)+(body[iBody].dYobl*body[iBody].dYobl)),body[iBody].dZobl);
  EccA = true2eccA(TrueA, Ecc);
  MeanL = EccA - Ecc*sin(EccA) + LongP;

  for (j=0;j<body[iBody].iNumLats;j++) {
    body[iBody].daAnnualInsol[j] = 0.0;
    body[iBody].daPeakInsol[j] = 0.0;
  }

  for (i=0;i<body[iBody].iNDays;i++) {
    if (i!=0) {
      MeanL = MeanL + 2*PI/body[iBody].iNDays;
      /* This will only work for the secular orbital model.
         Will need to be changed when/if resonances are added. */
      body[iBody].dMeanA = MeanL - LongP;
      kepler_eqn(body, iBody);
      EccA = body[iBody].dEccA;
      while (EccA >= 2*PI) EccA -= 2*PI;
      while (EccA < 0.0) EccA += 2*PI;
      if (EccA > PI) {
        TrueA = 2*PI - acos((cos(EccA) - Ecc)/(1.0 - Ecc*cos(EccA)));
      } else {
        TrueA = acos((cos(EccA) - Ecc)/(1.0 - Ecc*cos(EccA)));
      }
      body[iBody].dTrueL = TrueA + LongP;
    }

    while (body[iBody].dTrueL > 2*PI) body[iBody].dTrueL -= 2*PI;
    while (body[iBody].dTrueL < 0.0) body[iBody].dTrueL += 2*PI;

    // planet-star distance (units of semi-major axis):
    body[iBody].dAstroDist = (1.0 - (Ecc*Ecc))/(1.0+Ecc*cos(TrueA));

    DailyInsolation(body, iBody, i);

    for (j=0;j<body[iBody].iNumLats;j++) {
      body[iBody].daAnnualInsol[j] += body[iBody].daInsol[j][i]/((double)body[iBody].iNDays);
      if (body[iBody].daInsol[j][i] > body[iBody].daPeakInsol[j]) {
        body[iBody].daPeakInsol[j] = body[iBody].daInsol[j][i];
      }
    }
  }
}

/**
Calculates/updates the albedo at each latitude for the annual EBM

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void AlbedoAnnual(BODY *body, int iBody) {
 int i;

 for (i=0;i<body[iBody].iNumLats;i++) {
    if (body[iBody].dFixIceLat) {

      /* Cold poles */
      if (fabs(body[iBody].daLats[i]) > body[iBody].dFixIceLat) {
        body[iBody].daAlbedoAnn[i] = body[iBody].dIceAlbedo;
      } else {
        body[iBody].daAlbedoAnn[i] = body[iBody].dSurfAlbedo;
      }
    } else if (body[iBody].bAlbedoZA) {
       /* Use albedo based on zenith angle */
       body[iBody].daAlbedoAnn[i] = 0.31+0.04*(3*(sin(body[iBody].daLats[i])*sin(body[iBody].daLats[i]))-1);
    } else {
       if (body[iBody].daTempAnn[i] <= -10.0) {
         body[iBody].daAlbedoAnn[i] = body[iBody].dIceAlbedo;
       } else {
         body[iBody].daAlbedoAnn[i] = body[iBody].dSurfAlbedo;
       }
    }
  }
}

/**
Inverts the matrix for the annual EBM

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void MatrixInvertAnnual(BODY *body, int iBody) {
  double n = body[iBody].iNumLats;
  int i, j;
  float parity;

  LUDecomp(body[iBody].daMEulerAnn,body[iBody].daMEulerCopyAnn,body[iBody].daScaleAnn,body[iBody].iaRowswapAnn,n);
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++) {
      if (j==i) {
        body[iBody].daUnitVAnn[j] = 1.0;
      } else {
        body[iBody].daUnitVAnn[j] = 0.0;
      }
    }

    LUSolve(body[iBody].daMEulerCopyAnn,body[iBody].daUnitVAnn,body[iBody].iaRowswapAnn, n);
    for (j=0;j<n;j++) {
      body[iBody].daInvMAnn[j][i] = body[iBody].daUnitVAnn[j];
    }
  }
}

/**
Inverts the matrix for the seasonal EBM

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void MatrixInvertSeasonal(BODY *body, int iBody) {
  int n = 2*body[iBody].iNumLats;
  int i, j;
  float parity;

  LUDecomp(body[iBody].daMEulerSea,body[iBody].daMEulerCopySea,body[iBody].daScaleSea,body[iBody].iaRowswapSea,n);
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++) {
      if (j==i) {
        body[iBody].daUnitVSea[j] = 1.0;
      } else {
        body[iBody].daUnitVSea[j] = 0.0;
      }
    }

    LUSolve(body[iBody].daMEulerCopySea,body[iBody].daUnitVSea,body[iBody].iaRowswapSea, n);
    for (j=0;j<n;j++) {
      body[iBody].daInvMSea[j][i] = body[iBody].daUnitVSea[j];
    }
  }
}

/**
Calculates the approximate temperature gradient in latitude for the annual EBM

@param body Struct containing all body information and variables
@param delta_x Spacing of grid (x = sin(latitude))
@param iBody Body in question
*/
void TempGradientAnn(BODY *body, double delta_x, int iBody) {
  int i;

  body[iBody].daTGrad[0] = (body[iBody].daTempAnn[1]-body[iBody].daTempAnn[0])/(delta_x);
  for (i=1;i<body[iBody].iNumLats-1;i++) {
    body[iBody].daTGrad[i] = (body[iBody].daTempAnn[i+1]-body[iBody].daTempAnn[i-1])/(2*delta_x);
  }
  body[iBody].daTGrad[body[iBody].iNumLats-1] = (body[iBody].daTempAnn[body[iBody].iNumLats-1]-\
                          body[iBody].daTempAnn[body[iBody].iNumLats-2])/(delta_x);
}

/**
Calculates the approximate temperature gradient in latitude for the seasonal EBM

@param body Struct containing all body information and variables
@param delta_x Spacing of grid (x = sin(latitude))
@param iBody Body in question
*/
void TempGradientSea(BODY *body, double delta_x, int iBody) {
  int i;

  body[iBody].daTGrad[0] = (body[iBody].daTempLW[1]-body[iBody].daTempLW[0])/(delta_x);
  for (i=1;i<body[iBody].iNumLats-1;i++) {
    body[iBody].daTGrad[i] = (body[iBody].daTempLW[i+1]-body[iBody].daTempLW[i-1])/(2*delta_x);
  }
  body[iBody].daTGrad[body[iBody].iNumLats-1] = (body[iBody].daTempLW[body[iBody].iNumLats-1]-\
                          body[iBody].daTempLW[body[iBody].iNumLats-2])/(delta_x);
}

/**
Calculates the backwards-Euler matrix that integrates the annual EBM. Each
operation of the inverse matrix is a "time-step".

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void MatrixAnnual(BODY *body, int iBody) {
  int i, j;
  double delta_t, delta_x;

  delta_t = 1.5/body[iBody].iNumLats;
  delta_x = 2.0/body[iBody].iNumLats;

  for (i=0;i<body[iBody].iNumLats;i++) {
    body[iBody].daTempTerms[i] = 0.0;

    for (j=0;j<body[iBody].iNumLats;j++) {
      if (j==i) {
        body[iBody].daMClim[i][j] = (-body[iBody].daPlanckBAnn[i]-body[iBody].daLambdaAnn[i+1]-body[iBody].daLambdaAnn[i])/body[iBody].dHeatCapAnn;
        body[iBody].daMDiffAnn[i][j] = (-body[iBody].daLambdaAnn[i+1]-body[iBody].daLambdaAnn[i]);
        body[iBody].daMEulerAnn[i][j] = -1.0/delta_t;
      } else if (j==(i+1)) {
        body[iBody].daMClim[i][j] = body[iBody].daLambdaAnn[j]/body[iBody].dHeatCapAnn;
        body[iBody].daMDiffAnn[i][j] = body[iBody].daLambdaAnn[j];
        body[iBody].daMEulerAnn[i][j] = 0.0;
      } else if (j==(i-1)) {
        body[iBody].daMClim[i][j] = body[iBody].daLambdaAnn[i]/body[iBody].dHeatCapAnn;
        body[iBody].daMDiffAnn[i][j] = body[iBody].daLambdaAnn[i];
        body[iBody].daMEulerAnn[i][j] = 0.0;
      } else {
        body[iBody].daMClim[i][j] = 0.0;
        body[iBody].daMDiffAnn[i][j] = 0.0;
        body[iBody].daMEulerAnn[i][j] = 0.0;
      }
      body[iBody].daMEulerAnn[i][j] += 0.5*body[iBody].daMClim[i][j];
      body[iBody].daTempTerms[i] += body[iBody].daMClim[i][j]*body[iBody].daTempAnn[j];
    }
    body[iBody].daSourceF[i] = ((1.0-body[iBody].daAlbedoAnn[i])*body[iBody].daAnnualInsol[i] - \
                         body[iBody].daPlanckAAnn[i])/body[iBody].dHeatCapAnn;
    body[iBody].daTempTerms[i] += body[iBody].daSourceF[i];
  }
}

/**
Runs the annual EBM, called from ForceBehavior. The annual EBM runs to
steady-state (global temperature change becomes very small), rather than for a
set number of orbits.

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void PoiseAnnual(BODY *body, int iBody) {
  double delta_t, delta_x, xboundary, Tchange, tmpTglobal;
  int Nmax, i, j, n, k;

  /* Get current climate parameters */
  AlbedoAnnual(body, iBody);
  AnnualInsolation(body, iBody);
  if (body[iBody].bCalcAB) {
    for (i=0;i<=body[iBody].iNumLats;i++) {
      if (i!=body[iBody].iNumLats) {
        if (body[iBody].iOLRModel == WK97) {
          body[iBody].daPlanckBAnn[i] = dOLRdTwk97(body,iBody,i,ANN);
          body[iBody].daPlanckAAnn[i] = OLRwk97(body,iBody,i,ANN) \
            - body[iBody].daPlanckBAnn[i]*(body[iBody].daTempAnn[i]);
        } else if (body[iBody].iOLRModel == HM16) {
          body[iBody].daPlanckBAnn[i] = dOLRdThm16(body,iBody,i,ANN);
          body[iBody].daPlanckAAnn[i] = OLRhm16(body,iBody,i,ANN) \
            - body[iBody].daPlanckBAnn[i]*(body[iBody].daTempAnn[i]);
        } else {
          body[iBody].daPlanckBAnn[i] = dOLRdTsms09(body,iBody,i,ANN);
          body[iBody].daPlanckAAnn[i] = OLRsms09(body,iBody,i,ANN) \
            - body[iBody].daPlanckBAnn[i]*(body[iBody].daTempAnn[i]);
        }
      }

      if (body[iBody].bMEPDiff) {
        if (i==0) {
          body[iBody].daDiffusionAnn[i] = body[iBody].daPlanckBAnn[i]/4.0;
        } else if (i==body[iBody].iNumLats) {
          body[iBody].daDiffusionAnn[i] = body[iBody].daPlanckBAnn[i-1]/4.0;
        } else {
          body[iBody].daDiffusionAnn[i] = (body[iBody].daPlanckBAnn[i]+body[iBody].daPlanckBAnn[i-1])/8.0;
        }
      }
    }
  }

  delta_t = 1.5/body[iBody].iNumLats;
  delta_x = 2.0/body[iBody].iNumLats;
  Nmax = 2000;

  /* Setup matrices, source function, temperature terms, global mean */
  for (i=0;i<body[iBody].iNumLats+1;i++) {
    xboundary = -1.0 + i*2.0/body[iBody].iNumLats;
    body[iBody].daLambdaAnn[i] = body[iBody].daDiffusionAnn[i]*(1.0-(xboundary*xboundary))/((delta_x*delta_x));
  }

  body[iBody].dTGlobal = 0.0;
  for (i=0;i<body[iBody].iNumLats;i++) {
    body[iBody].dTGlobal += body[iBody].daTempAnn[i]/body[iBody].iNumLats;
  }
  MatrixAnnual(body, iBody);
  MatrixInvertAnnual(body,iBody);

  /* Relaxation to equilibrium */
  n = 1;
  Tchange = 1.0;
  while (fabs(Tchange) > 1e-12) {
    tmpTglobal = 0.0;
    for (i=0;i<body[iBody].iNumLats;i++) {
      body[iBody].daTmpTempAnn[i] = 0.0;

      for (j=0;j<body[iBody].iNumLats;j++) {
        body[iBody].daTmpTempAnn[i] += -body[iBody].daInvMAnn[i][j]*(0.5*(body[iBody].daTempTerms[j]+body[iBody].daSourceF[j])+body[iBody].daTempAnn[j]/delta_t);
      }
      tmpTglobal += body[iBody].daTmpTempAnn[i]/body[iBody].iNumLats;
    }

    for (i=0;i<body[iBody].iNumLats;i++) {
      body[iBody].daTmpTempTerms[i] = body[iBody].daSourceF[i];

      for (j=0;j<body[iBody].iNumLats;j++) {
        body[iBody].daTmpTempTerms[i] += body[iBody].daMClim[i][j]*body[iBody].daTmpTempAnn[j];
      }
    }

    Tchange = tmpTglobal - body[iBody].dTGlobal;

    /* Update albedo, source function, temperature, temperature terms, and global mean */
    AlbedoAnnual(body,iBody);
    for (i=0;i<body[iBody].iNumLats;i++) {
      body[iBody].daSourceF[i] = ((1.0-body[iBody].daAlbedoAnn[i])*body[iBody].daAnnualInsol[i] - \
                         body[iBody].daPlanckAAnn[i])/body[iBody].dHeatCapAnn;
      body[iBody].daTempAnn[i] = body[iBody].daTmpTempAnn[i];
      body[iBody].daTempTerms[i] = body[iBody].daTmpTempTerms[i];
      body[iBody].dTGlobal = tmpTglobal;
    }
    if (n >= Nmax) {
      fprintf(stderr,"POISE solution not converged before max iterations reached.\n");
      exit(EXIT_INPUT);
    }
    if (body[iBody].bCalcAB == 1) {
      for (i=0;i<=body[iBody].iNumLats;i++) {
        if (i!=body[iBody].iNumLats) {
          if (body[iBody].iOLRModel == WK97) {
            body[iBody].daPlanckBAnn[i] = dOLRdTwk97(body,iBody,i,ANN);
            body[iBody].daPlanckAAnn[i] = OLRwk97(body,iBody,i,ANN) \
              - body[iBody].daPlanckBAnn[i]*(body[iBody].daTempAnn[i]);
          } else if (body[iBody].iOLRModel == HM16) {
            body[iBody].daPlanckBAnn[i] = dOLRdThm16(body,iBody,i,ANN);
            body[iBody].daPlanckAAnn[i] = OLRhm16(body,iBody,i,ANN) \
              - body[iBody].daPlanckBAnn[i]*(body[iBody].daTempAnn[i]);
          } else {
            body[iBody].daPlanckBAnn[i] = dOLRdTsms09(body,iBody,i,ANN);
            body[iBody].daPlanckAAnn[i] = OLRsms09(body,iBody,i,ANN) \
              - body[iBody].daPlanckBAnn[i]*(body[iBody].daTempAnn[i]);
          }
        }

        if (body[iBody].bMEPDiff) {
          if (i==0) {
            body[iBody].daDiffusionAnn[i] = body[iBody].daPlanckBAnn[i]/4.0;
          } else if (i==body[iBody].iNumLats) {
            body[iBody].daDiffusionAnn[i] = body[iBody].daPlanckBAnn[i-1]/4.0;
          } else {
            body[iBody].daDiffusionAnn[i] = (body[iBody].daPlanckBAnn[i]+body[iBody].daPlanckBAnn[i-1])/8.0;
          }
          xboundary = -1.0 + i*2.0/body[iBody].iNumLats;
          body[iBody].daLambdaAnn[i] = body[iBody].daDiffusionAnn[i]*\
                    (1.0-(xboundary*xboundary))/((delta_x*delta_x));
        }
      }
      MatrixAnnual(body, iBody);
      MatrixInvertAnnual(body,iBody);
    }
    n++;
  }

  /* Calculate some interesting quantities */
  body[iBody].dFluxInGlobal = 0.0;
  body[iBody].dFluxOutGlobal = 0.0;
  body[iBody].dAlbedoGlobal = 0.0;
  body[iBody].dIceMassTot = 0.0;
  TempGradientAnn(body, delta_x, iBody);
  for (i=0;i<body[iBody].iNumLats;i++) {
    body[iBody].daDMidPt[i] = 0.5*(body[iBody].daDiffusionAnn[i+1]+body[iBody].daDiffusionAnn[i]);
    body[iBody].daFlux[i] = -2.*PI*(body[iBody].dRadius*body[iBody].dRadius)*sqrt(1.0-(sin(body[iBody].daLats[i])*sin(body[iBody].daLats[i]))) * \
                            body[iBody].daDMidPt[i]*body[iBody].daTGrad[i];
    body[iBody].daFluxIn[i] = (1.0 - body[iBody].daAlbedoAnn[i])*body[iBody].daAnnualInsol[i];
    body[iBody].daFluxOut[i] = body[iBody].daPlanckAAnn[i] + body[iBody].daPlanckBAnn[i]*body[iBody].daTempAnn[i];

    body[iBody].dFluxInGlobal += body[iBody].daFluxIn[i]/body[iBody].iNumLats;
    body[iBody].dFluxOutGlobal += body[iBody].daFluxOut[i]/body[iBody].iNumLats;

    body[iBody].daDivFlux[i] = 0.0;
    for (j=0;j<body[iBody].iNumLats;j++) {
      body[iBody].daDivFlux[i] += -body[iBody].daMDiffAnn[i][j]*body[iBody].daTempAnn[j];
    }
    body[iBody].dAlbedoGlobal += body[iBody].daAlbedoAnn[i]/body[iBody].iNumLats;
  }
}

/**
Calculates the OLR from the Haqq-Misra+ 2016 formulae (currently NOT well
trusted by this developer).

@param body Struct containing all body information
@param iBody Body in question
@param iLat Latitude at which you want to calculate the OLR
@param bModel Type of EBM (annual or seasonal)
*/
double OLRhm16(BODY *body, int iBody, int iLat, int bModel) {
  double phi, Int, tmpk, f, dT;

  phi = log10(body[iBody].dpCO2);
  if (bModel == ANN) {
    dT = body[iBody].daTempAnn[iLat]+273.15;
  } else {
    dT = body[iBody].daTempLW[iLat]+273.15;
  }
  if (dT > 150) {
    tmpk = log10(dT);
    f = 9.12805643869791438760*(tmpk*tmpk*tmpk*tmpk)+4.58408794768168803557*(tmpk*tmpk*tmpk)*phi- \
        8.47261075643147449910e+01*(tmpk*tmpk*tmpk)+4.35517381112690282752e-01*(tmpk*phi*tmpk*phi)-\
        2.86355036260417961103e+01*(tmpk*tmpk)*phi+2.96626642498045896446e+02*(tmpk*tmpk)-\
        6.01082900358299240806e-02*tmpk*(phi*phi*phi)-2.60414691486954641420*tmpk*(phi*phi)+\
        5.69812976563675661623e+01*tmpk*phi-4.62596100127381816947e+02*tmpk+\
        2.18159373001564722491e-03*(phi*phi*phi*phi)+1.61456772400726950023e-01*(phi*phi*phi)+\
        3.75623788187470086797*(phi*phi)-3.53347289223180354156e+01*phi+\
        2.75011005409836684521e+02;
    Int = pow(10.0,f)/1000.;
  } else {
    Int = SIGMA * dT*dT*dT*dT; //very cold brrr....
  }
  return Int;
}

/**
Calculates the slope of the OLR from the Haqq-Misra+ 2016 formulae (currently
NOT well trusted by this developer).

@param body Struct containing all body information
@param iBody Body in question
@param iLat Latitude at which you want to calculate the OLR
@param bModel Type of EBM (annual or seasonal)
*/
double dOLRdThm16(BODY *body, int iBody, int iLat, int bModel) {
  double phi, dI, tmpk, f, dT;

  phi = log10(body[iBody].dpCO2);
  if (bModel == ANN) {
    dT = body[iBody].daTempAnn[iLat]+273.15;
  } else {
    dT = body[iBody].daTempLW[iLat]+273.15;
  }
    tmpk = log10(dT);
    f = 4*9.12805643869791438760*(tmpk*tmpk*tmpk)+3*4.58408794768168803557*(tmpk*tmpk)*phi- \
      3*8.47261075643147449910e+01*(tmpk*tmpk)+2*4.35517381112690282752e-01*tmpk*(phi*phi)-\
      2*2.86355036260417961103e+01*tmpk*phi+2*2.96626642498045896446e+02*tmpk-\
      6.01082900358299240806e-02*(phi*phi*phi)-2.60414691486954641420*(phi*phi)+\
      5.69812976563675661623e+01*phi-4.62596100127381816947e+02;
    dI = OLRhm16(body,iBody,iLat,bModel) * f / (body[iBody].daTempLW[iLat]+273.15);

    if (dI <= 0) {
      dI = dOLRdTwk97(body,iBody,iLat,bModel);
    }
  return dI;
}

/**
Calculates the OLR from the Spiegel+ 2009 formulae

@param body Struct containing all body information
@param iBody Body in question
@param iLat Latitude at which you want to calculate the OLR
@param bModel Type of EBM (annual or seasonal)
*/
double OLRsms09(BODY *body, int iBody, int iLat, int bModel) {
  double tau, Int, T;

  if (bModel == ANN) {
    T = body[iBody].daTempAnn[iLat]+273.15;
  } else {
    T = body[iBody].daTempLW[iLat]+273.15;
  }
  tau = 0.79*(T/273.15)*(T/273.15)*(T/273.15);

  Int = SIGMA*T*T*T*T/(1.0+0.75*tau);
  return Int;
}

/**
Calculates the slope of the OLR from the Spiegel+ 2009 formulae

@param body Struct containing all body information
@param iBody Body in question
@param iLat Latitude at which you want to calculate the OLR
@param bModel Type of EBM (annual or seasonal)
*/
double dOLRdTsms09(BODY *body, int iBody, int iLat, int bModel) {
  double tau, dtau, dI, T;

  if (bModel == ANN) {
    T = body[iBody].daTempAnn[iLat]+273.15;
  } else {
    T = body[iBody].daTempLW[iLat]+273.15;
  }
  tau = 0.79*(T/273.15)*(T/273.15)*(T/273.15);
  dtau = 3.0*0.79*T*T/(273.15*273.15*273.15);

  dI = SIGMA*(4*T*T*T/(1.0+0.75*tau)-T*T*T*T/(1.+0.75*tau)/(1.+0.75*tau)*0.75*tau*dtau);
  return dI;
}

/**
Calculates the OLR from the Williams & Kasting 1997 formulae (currently NOT well
trusted by this developer).

@param body Struct containing all body information
@param iBody Body in question
@param iLat Latitude at which you want to calculate the OLR
@param bModel Type of EBM (annual or seasonal)
*/
double OLRwk97(BODY *body, int iBody, int iLat, int bModel){
  double phi, Int, T;

  phi = log(body[iBody].dpCO2/3.3e-4);
  if (bModel == ANN) {
    T = body[iBody].daTempAnn[iLat]+273.15;
  } else {
    T = body[iBody].daTempLW[iLat]+273.15;
  }
  Int = 9.468980 - 7.714727e-5*phi - 2.794778*T - 3.244753e-3*phi*T-3.547406e-4*(phi*phi) \
      + 2.212108e-2*(T*T) + 2.229142e-3*(phi*phi)*T + 3.088497e-5*phi*(T*T) \
      - 2.789815e-5*(phi*T*phi*T) - 3.442973e-3*(phi*phi*phi) - 3.361939e-5*(T*T*T) \
      + 9.173169e-3*(phi*phi*phi)*T - 7.775195e-5*(phi*phi*phi)*(T*T) \
      - 1.679112e-7*phi*(T*T*T) + 6.590999e-8*(phi*phi)*(T*T*T) \
      + 1.528125e-7*(phi*phi*phi)*(T*T*T) - 3.367567e-2*(phi*phi*phi*phi) - 1.631909e-4*(phi*phi*phi*phi)*T \
      + 3.663871e-6*(phi*phi*phi*phi)*(T*T) - 9.255646e-9*(phi*phi*phi*phi)*(T*T*T);
  if (Int >= 300) {
    Int = 300.0;
  }
  if (T < 190) {
    Int = SIGMA * T*T*T*T;
  }
  return Int;
}

/**
Calculates the slope of the  OLR from the Williams & Kasting 1997 formulae
 (currently NOT well trusted by this developer).

@param body Struct containing all body information
@param iBody Body in question
@param iLat Latitude at which you want to calculate the OLR
@param bModel Type of EBM (annual or seasonal)
*/
double dOLRdTwk97(BODY *body, int iBody, int iLat, int bModel){
  double phi, dI, T;

  phi = log(body[iBody].dpCO2/3.3e-4);
  if (bModel == ANN) {
    //printf("%lf\n",body[iBody].daTempAnn[iLat]);
    T = body[iBody].daTempAnn[iLat]+273.15;
  } else {
    // MEM: body[iBody].daTempLW[iLat] is not initialized!
    T = body[iBody].daTempLW[iLat]+273.15;
  }
  dI = - 2.794778 + 2*2.212108e-2*T - 3*3.361939e-5*(T*T) - 3.244753e-3*phi \
       + 2*3.088497e-5*phi*T - 3*1.679112e-7*phi*(T*T) + 2.229142e-3*(phi*phi) \
       - 2*2.789815e-5*(phi*phi)*T + 3*6.590999e-8*(phi*phi)*(T*T) \
       + 9.173169e-3*(phi*phi*phi) - 2*7.775195e-5*(phi*phi*phi)*T \
       + 3*1.528125e-7*(phi*phi*phi)*(T*T) - 1.631909e-4*(phi*phi*phi*phi) \
       + 2*3.663871e-6*(phi*phi*phi*phi)*T - 3*9.255646e-9*(phi*phi*phi*phi)*(T*T);
  if (OLRwk97(body,iBody,iLat,bModel)>=300.0) {
    dI = 0.001;
  }

  if (T<190) {
    dI = 4*SIGMA *T*T*T;
  }
  return dI;
}

/**
Calculates the "top-of-atmosphere" from the Haqq-Misra+ 2016 formulae
 (currently NOT well trusted by this developer) at temperatures < 250 K

@param Temp Temperature at grid point
@param pCO2 Atmospheric partial pressure of CO2
@param zenith Zenith angle of host star on sky
@param albsurf Base albedo quantity of surface (ice/water/land)
*/
double AlbedoTOA250(double Temp, double phi, double zenith, double albsurf) {
  double mu, tmpk, dTmp;
  mu = cos(zenith);
  tmpk = log10(Temp+273.15);

  dTmp = -3.64301272050786051349e-01*mu*mu*mu-6.66571453035937344644e-01*mu*mu*albsurf+\
     1.38761634791769922215e-01*mu*mu*tmpk-1.40826323888164368220e-02*mu*mu*phi+\
     9.41440608298288128530e-01*mu*mu+7.10961643487220129600e-02*mu*albsurf*albsurf-\
     2.19180456421237290776e-01*mu*albsurf*tmpk-1.82873271476295846949e-02*mu*albsurf*phi+\
     1.48505536251773073708e+00*mu*albsurf-9.01309617860975631487e-01*mu*tmpk*tmpk+\
     1.92113767482554841093e-02*mu*tmpk*phi+4.11334031794617160926e+00*mu*tmpk+\
     6.80906172782627400891e-04*mu*phi*phi-1.66632232847024261413e-02*mu*phi-\
     6.01321219414692986760e+00*mu+5.20833333338503734478e-02*albsurf*albsurf*albsurf+\
     1.09511892935421337181e-01*albsurf*albsurf*tmpk+\
     1.86369741605604787027e-02*albsurf*albsurf*phi-2.54092206932019781807e-01*albsurf*albsurf-\
     4.00290429315177131997e+00*albsurf*tmpk*tmpk-\
     4.60694421170402754195e-02*albsurf*tmpk*phi+1.79103047870275950970e+01*albsurf*tmpk-\
     1.59834667195196747369e-02*albsurf*phi*phi-1.29954198131196525801e-02*albsurf*phi-\
     1.97041106668471570629e+01*albsurf-9.28987827590191805882e+00*tmpk*tmpk*tmpk+\
     2.33079221557892068972e-01*tmpk*tmpk*phi+6.58750181054108310263e+01*tmpk*tmpk+
     7.46763857253681870296e-03*tmpk*phi*phi-1.00561681124449076030e+00*tmpk*phi-\
     1.55355955538023465579e+02*tmpk+7.11268878229609079374e-04*phi*phi*phi-\
     3.36136500021004319336e-03*phi*phi+1.13977221457453326003e+00*phi+\
     1.22439629486842392225e+02;

  return dTmp;
}

/**
Calculates the "top-of-atmosphere" from the Haqq-Misra+ 2016 formulae
 (currently NOT well trusted by this developer) at 250 K < temperatures < 350 K

@param Temp Temperature at grid point
@param pCO2 Atmospheric partial pressure of CO2
@param zenith Zenith angle of host star on sky
@param albsurf Base albedo quantity of surface (ice/water/land)
*/
double AlbedoTOA350(double Temp, double phi, double zenith, double albsurf) {
  double mu, tmpk, dTmp;
  mu = cos(zenith);
  tmpk = log10(Temp+273.15);

  dTmp = -4.41391619954555503025e-01*mu*mu*mu-2.60017516002879089942e-01*mu*mu*albsurf+\
     1.08110772295329837789e+00*mu*mu*tmpk-3.93863285843020910493e-02*mu*mu*phi-\
     1.46383456258096611435e+00*mu*mu+9.91383778608142668398e-02*mu*albsurf*albsurf-\
     1.45914724229303338632e+00*mu*albsurf*tmpk-2.72769392852398387395e-02*mu*albsurf*phi+\
     3.99933641081463919775e+00*mu*albsurf+1.07231336256525633388e+00*mu*tmpk*tmpk-\
     1.04302520934751417891e-02*mu*tmpk*phi-6.10296439299006454604e+00*mu*tmpk+\
     2.69255203910960137434e-03*mu*phi*phi+9.50143253373007257157e-02*mu*phi+\
     7.37864215757422226005e+00*mu+1.28580729156335171748e-01*albsurf*albsurf*albsurf-\
     3.07800300913486257759e-01*albsurf*albsurf*tmpk+\
     2.27715594632176554502e-02*albsurf*albsurf*phi+6.11699085276039222769e-01*albsurf*albsurf-\
     2.33213409642421742873e+00*albsurf*tmpk*tmpk+\
     2.56011431303802661219e-01*albsurf*tmpk*phi+1.05912148222549546972e+01*albsurf*tmpk-\
     1.85772688884413561539e-02*albsurf*phi*phi-7.55796861024326749323e-01*albsurf*phi-\
     1.16485004141808623501e+01*albsurf+2.74062491988752192640e+01*tmpk*tmpk*tmpk+\
     5.46044240911252587445e-01*tmpk*tmpk*phi-2.05761674358916081928e+02*tmpk*tmpk+\
     5.57943359123403426203e-02*tmpk*phi*phi-2.49880329758542751861e+00*tmpk*phi+\
     5.14448995054491206247e+02*tmpk+2.43702089287719950508e-03*phi*phi*phi-\
     1.09384840764980617589e-01*phi*phi+2.92643187434628071486e+00*phi-
     4.27802454850920923946e+02;

  return dTmp;
}

/**
Calculates the "top-of-atmosphere" from the Williams & Kasting 1997 formulae
 (currently NOT well trusted by this developer) at temperatures < 280 K

@param Temp Temperature at grid point
@param pCO2 Atmospheric partial pressure of CO2
@param zenith Zenith angle of host star on sky
@param albsurf Base albedo quantity of surface (ice/water/land)
*/
double AlbedoTOA280(double Temp, double pCO2, double zenith, double albsurf) {
  double mu, T, dTmp;
  mu = cos(zenith);
  T = Temp+273.15;

  dTmp = -6.891e-1 + 1.046*albsurf + 7.8054e-3*T - 2.8373e-3*pCO2 - 2.8899e-1*mu \
      - 3.7412e-2*albsurf*pCO2 - 6.3499e-3*mu*pCO2 + 2.0122e-1*albsurf*mu \
      - 1.8508e-3*albsurf*T + 1.3649e-4*mu*T + 9.8581e-5*pCO2*T \
      + 7.3239e-2*albsurf*albsurf - 1.6555e-5*(T*T) + 6.5817e-4*(pCO2*pCO2) \
      + 8.1218e-2*mu*mu;

  return dTmp;
}

/**
Calculates the "top-of-atmosphere" from the Williams & Kasting 1997 formulae
 (currently NOT well trusted by this developer) at 280 K < temperatures < 370 K

@param Temp Temperature at grid point
@param pCO2 Atmospheric partial pressure of CO2
@param zenith Zenith angle of host star on sky
@param albsurf Base albedo quantity of surface (ice/water/land)
*/
double AlbedoTOA370(double Temp, double pCO2, double zenith, double albsurf) {
  double mu, T, dTmp;
  mu = cos(zenith);
  T = Temp+273.15;

  dTmp =  1.1082 + 1.5172*albsurf - 5.7993e-3*T + 1.9705e-2*pCO2 - 1.867e-1*mu \
      - 3.1355e-2*albsurf*pCO2 - 1.0214e-2*mu*pCO2 + 2.0986e-1*albsurf*mu \
      - 3.7098e-3*albsurf*T - 1.1335e-4*mu*T + 5.3714e-5*pCO2*T \
      + 7.5887e-2*albsurf*albsurf + 9.269e-6*(T*T) - 4.1327e-4*(pCO2*pCO2) \
      + 6.3298e-2*mu*mu;

  return dTmp;
}

/**
Calculates albedo based on zenith angle (tuned to Earth)

@param zenith Zenith angle of each latitude in radians
@return Albedo
*/
double AlbedoTaylor(double zenith) {
  double mu = cos(zenith);

  if (mu > 0) {
    return 0.037/(1.1*pow(mu,1.4)+0.15);
  } else {
    return 0.037/0.15;
  }
}

/**
Calculates the planetary albedo based on the formulae from Haqq-Misra+ 2016,
accounting for temperature and surface type.

@param body Struct containing all body information
@param zenith Zenith angle of latitude iLat
@param iBody Body in question
@param iLat Latitude cell in question
*/
void AlbedoTOAhm16(BODY *body, double zenith, int iBody, int iLat) {
  double phi = log10(body[iBody].dpCO2), albtmp;

  if (body[iBody].daIceMassTmp[iLat] > 0 || body[iBody].daTempLand[iLat] <= -10) {
    albtmp = body[iBody].dIceAlbedo;
  } else {
    albtmp = body[iBody].dAlbedoLand;
  }

  if (body[iBody].daTempLand[iLat] <= (-23.15)) {
    body[iBody].daAlbedoLand[iLat] = AlbedoTOA250(body[iBody].daTempLand[iLat],phi,zenith,albtmp);
  } else if (body[iBody].daTempLand[iLat] <= 76.85) {
    body[iBody].daAlbedoLand[iLat] = AlbedoTOA350(body[iBody].daTempLand[iLat],phi,zenith,albtmp);
  } else {
    body[iBody].daAlbedoLand[iLat] = 0.18;
  }

  if (body[iBody].daTempWater[iLat] <= body[iBody].dFrzTSeaIce) {
    albtmp = body[iBody].dIceAlbedo;
  } else {
    albtmp = AlbedoTaylor(zenith);
  }

  if (body[iBody].daTempWater[iLat] <= (-23.15)) {
    body[iBody].daAlbedoWater[iLat] = AlbedoTOA250(body[iBody].daTempWater[iLat],phi,zenith,albtmp);
  } else if (body[iBody].daTempWater[iLat] <= 76.85) {
    body[iBody].daAlbedoWater[iLat] = AlbedoTOA350(body[iBody].daTempWater[iLat],phi,zenith,albtmp);
  } else {
    body[iBody].daAlbedoWater[iLat] = 0.18; //albedo asymptotes to ~0.18 (all surface albedos?)
  }
}


/**
Calculates the planetary albedo based on the formulae from Williams & Kasting
1997, accounting for temperature and surface type.

@param body Struct containing all body information
@param zenith Zenith angle of latitude iLat
@param iBody Body in question
@param iLat Latitude cell in question
*/
void AlbedoTOAwk97(BODY *body, double zenith, int iBody, int iLat) {
  double phi = body[iBody].dpCO2, albtmp;

  if (body[iBody].daTempLand[iLat] <= -10) {
    albtmp = body[iBody].dIceAlbedo;
  } else if (body[iBody].daTempLand[iLat] > -10 && body[iBody].daIceMassTmp[iLat] > 0) {
    albtmp = (body[iBody].dIceAlbedo+body[iBody].dAlbedoLand)/2.0;
  } else if (body[iBody].daTempLand[iLat] <= 0 && body[iBody].daIceMassTmp[iLat] == 0) {
    albtmp = (body[iBody].dIceAlbedo+body[iBody].dAlbedoLand)/2.0;
  } else {
    albtmp = body[iBody].dAlbedoLand;
  }

  if (body[iBody].daTempLand[iLat] >= -83.15 && body[iBody].daTempLand[iLat] <= (6.85)) {
    body[iBody].daAlbedoLand[iLat] = AlbedoTOA280(body[iBody].daTempLand[iLat],phi,zenith,albtmp);
  } else if (body[iBody].daTempLand[iLat] <= 96.85) {
    body[iBody].daAlbedoLand[iLat] = AlbedoTOA370(body[iBody].daTempLand[iLat],phi,zenith,albtmp);
  } else if (body[iBody].daTempLand[iLat] < -83.15) {
    body[iBody].daAlbedoLand[iLat] = body[iBody].dIceAlbedo;
  } else {
    body[iBody].daAlbedoLand[iLat] = 0.18; //albedo asymptotes to ~0.18 (all surface albedos?)
  }

  if (body[iBody].daTempWater[iLat] <= body[iBody].dFrzTSeaIce) {
    albtmp = body[iBody].dIceAlbedo;
  } else {
    albtmp = AlbedoTaylor(zenith);
  }

  if (body[iBody].daTempWater[iLat] >= -83.15 && body[iBody].daTempWater[iLat] <= (6.85)) {
    body[iBody].daAlbedoWater[iLat] = AlbedoTOA280(body[iBody].daTempWater[iLat],phi,zenith,albtmp);
  } else if (body[iBody].daTempWater[iLat] <= 96.85) {
    body[iBody].daAlbedoWater[iLat] = AlbedoTOA370(body[iBody].daTempWater[iLat],phi,zenith,albtmp);
  } else if (body[iBody].daTempWater[iLat] < -83.15) {
    body[iBody].daAlbedoWater[iLat] = body[iBody].dIceAlbedo;
  } else {
    body[iBody].daAlbedoWater[iLat] = 0.18; //albedo asymptotes to ~0.18 (all surface albedos?)
  }
}

/**
Calculates the planetary albedo based on the formulae from Spiegel+ 2009,
 accounting for temperature and surface type.

@param body Struct containing all body information
@param zenith Zenith angle of latitude iLat
@param iBody Body in question
@param iLat Latitude cell in question
*/
void AlbedoTOAsms09(BODY *body, double zenith, int iBody, int iLat) {
  body[iBody].daAlbedoLand[iLat] = 0.5*(body[iBody].dIceAlbedo+body[iBody].dAlbedoLand)-\
        0.5*(body[iBody].dIceAlbedo-body[iBody].dAlbedoLand)*\
        tanh((body[iBody].daTempLand[iLat]+5.15)/5.15)\
        +0.04*(3.*sin(zenith)*sin(zenith)-1.);
  body[iBody].daAlbedoWater[iLat] = 0.5*(body[iBody].dIceAlbedo+body[iBody].dAlbedoWater)-\
        0.5*(body[iBody].dIceAlbedo-body[iBody].dAlbedoWater)*\
        tanh((body[iBody].daTempWater[iLat]+5.15)/5.15)\
        +0.04*(3.*sin(zenith)*sin(zenith)-1.);
  if (body[iBody].daIceMassTmp[iLat] > 0 && body[iBody].daAlbedoLand[iLat] < body[iBody].dIceAlbedo) {
      body[iBody].daAlbedoLand[iLat] = body[iBody].dIceAlbedo;
  }
}

/**
Calculates the planetary albedo for the seasonal EBM at day iDay

@param body Struct containing all body information
@param iBody Body in question
@param iDay Day of the planet's year
*/
void AlbedoSeasonal(BODY *body, int iBody, int iDay) {
  int iLat;
  double zenith;

  body[iBody].dAlbedoGlobalTmp = 0;
  for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
    //zenith angle of sun at noon at each latitude
    zenith = fabs(body[iBody].daLats[iLat] - body[iBody].daDeclination[iDay]);

    if (body[iBody].bCalcAB == 1) {
      if (body[iBody].iOLRModel == WK97) {
        AlbedoTOAwk97(body, zenith, iBody, iLat);
      } else if (body[iBody].iOLRModel == HM16) {
        AlbedoTOAhm16(body, zenith, iBody, iLat);
//         AlbedoTOAwk97(body, zenith, iBody, iLat);
      } else {
        AlbedoTOAsms09(body, zenith, iBody, iLat);
      }
    } else {
      body[iBody].daAlbedoLand[iLat] = body[iBody].dAlbedoLand+0.08*(3.*(sin(zenith)*sin(zenith))-1.)/2.;
      body[iBody].daAlbedoWater[iLat] = body[iBody].dAlbedoWater+0.08*(3.*(sin(zenith)*sin(zenith))-1.)/2.;
      if (body[iBody].daIceMassTmp[iLat] > 0 || body[iBody].daTempLand[iLat] <= -2) {
        body[iBody].daAlbedoLand[iLat] = body[iBody].dIceAlbedo;
      }
      if (body[iBody].daTempWater[iLat] <= body[iBody].dFrzTSeaIce) {
        body[iBody].daAlbedoWater[iLat] = body[iBody].dIceAlbedo;
      }
    }
    body[iBody].daAlbedoLW[iLat] = body[iBody].daLandFrac[iLat]*body[iBody].daAlbedoLand[iLat]+ \
                              body[iBody].daWaterFrac[iLat]*body[iBody].daAlbedoWater[iLat];
    body[iBody].dAlbedoGlobalTmp += body[iBody].daAlbedoLW[iLat]/body[iBody].iNumLats;
  }
  body[iBody].dAlbedoGlobal += \
            body[iBody].dAlbedoGlobalTmp/(body[iBody].iNStepInYear);
}

/**
Modifies the ocean component to account for effects of sea ice (seasonal EBM
only). This slows the EBM considerably so use with caution.

@param body Struc containing all body information
@param iBody Body in question
*/
void SeaIce(BODY *body, int iBody) {
  int i, j;
  double nhicearea=0, shicearea=0, nhtotarea=0, shtotarea=0, nhfw, shfw, nhdW, shdW, Cw_dt;
  Cw_dt = (body[iBody].dHeatCapWater*body[iBody].dMeanMotion/(2*PI))/body[iBody].dSeasDeltat;

  for (i=0;i<2*body[iBody].iNumLats;i++) {
    for (j=0;j<2*body[iBody].iNumLats;j++) {
      body[iBody].daMEulerSea[i][j] = body[iBody].daMInit[i][j];
    }
  }

  for (i=0;i<body[iBody].iNumLats;i++) {
    if (body[iBody].daTempWater[i] <= body[iBody].dFrzTSeaIce) {
      if (body[iBody].daSeaIceHeight[i] > 0) {
        body[iBody].daSeaIceK[i] = body[iBody].dSeaIceConduct/body[iBody].daSeaIceHeight[i];
        body[iBody].daSourceLW[2*i+1] = body[iBody].daSeaIceK[i]*body[iBody].dFrzTSeaIce \
            - body[iBody].daSourceW[i];
        body[iBody].daMEulerSea[2*i+1][2*i+1] += -Cw_dt+body[iBody].daSeaIceK[i];
      } else {
        body[iBody].daSeaIceK[i] = 0.0;
      }
    }
  }
  MatrixInvertSeasonal(body,iBody);

  for (i=0;i<2*body[iBody].iNumLats;i++) {
    body[iBody].daTmpTempSea[i] = 0.0;
    for (j=0;j<2*body[iBody].iNumLats;j++) {
      body[iBody].daTmpTempSea[i] += body[iBody].daInvMSea[i][j]*body[iBody].daSourceLW[j];
    }
  }

  for (i=0;i<body[iBody].iNumLats;i++) {
    //temp change this time step
    body[iBody].daDeltaTempL[i] = body[iBody].daTmpTempSea[2*i]-body[iBody].daTempLand[i];
    body[iBody].daDeltaTempW[i] = body[iBody].daTmpTempSea[2*i+1]-body[iBody].daTempWater[i];

    body[iBody].daTempLand[i] = body[iBody].daTmpTempSea[2*i];
    body[iBody].daTempWater[i] = body[iBody].daTmpTempSea[2*i+1];

    /* if sea ice present but T > -2, set to -2 */
    if (body[iBody].daSeaIceHeight[i] > 0) {
      if (body[iBody].daTempWater[i] > -2) {
        body[iBody].daTempWater[i] = -2.0;
      }

      body[iBody].daFluxSeaIce[i] = -body[iBody].daSourceW[i]-body[iBody].daPlanckBSea[i] \
              *body[iBody].daTempWater[i] - body[iBody].dNuLandWater/body[iBody].daWaterFrac[i]\
              *(body[iBody].daTmpTempSea[2*i+1]-body[iBody].daTempLand[i]);
      for (j=0;j<body[iBody].iNumLats;j++) {
        body[iBody].daFluxSeaIce[i] += body[iBody].daMDiffSea[i][j]*body[iBody].daTmpTempSea[2*j+1];
      }
      if (body[iBody].daLats[i] >= 0) {
        nhicearea += body[iBody].daWaterFrac[i];
        nhtotarea += body[iBody].daWaterFrac[i];
      } else {
        shicearea += body[iBody].daWaterFrac[i];
        shtotarea += body[iBody].daWaterFrac[i];
      }
    } else {
      body[iBody].daFluxSeaIce[i] = 0.0;
      /* no sea ice, still add to total area */
      if (body[iBody].daLats[i] >= 0) {
        nhtotarea += body[iBody].daWaterFrac[i];
      } else {
        shtotarea += body[iBody].daWaterFrac[i];
      }
    }
  }
  nhfw = 2.0*(2.0-2.0*(nhicearea - body[iBody].dSeasDeltax)/nhtotarea);
  shfw = 2.0*(2.0-2.0*(shicearea - body[iBody].dSeasDeltax)/shtotarea);
  if (nhfw > 4) nhfw = 4.0;
  if (shfw > 4) shfw = 4.0;
  nhdW = nhfw*nhicearea/(nhtotarea-nhicearea)/Cw_dt;
  shdW = shfw*shicearea/(shtotarea-shicearea)/Cw_dt;

  for (i=0;i<body[iBody].iNumLats;i++) {
    if (body[iBody].daSeaIceHeight[i] > 0) {
      if (body[iBody].daLats[i] >= 0) {
        body[iBody].daFluxSeaIce[i] += nhfw;
      } else {
        body[iBody].daFluxSeaIce[i] += shfw;
      }
    } else {
      if (body[iBody].daLats[i] >= 0) {
        body[iBody].daTempWater[i] -= nhdW;
      } else {
        body[iBody].daTempWater[i] -= shdW;
      }
    }
  }
}

/**
Calculates the backwards-Euler matrix that integrates the seasonal EBM. Each
operation of the inverse matrix is a "time-step".

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void MatrixSeasonal(BODY *body, int iBody) {
  int i, j;
  double xboundary, nu_fl, nu_fw, Cl_dt, Cw_dt, dt_Lf;
  Cl_dt = body[iBody].dHeatCapLand*body[iBody].dMeanMotion/(2*PI)/body[iBody].dSeasDeltat;
  Cw_dt = body[iBody].dHeatCapWater*body[iBody].dMeanMotion/(2*PI)/body[iBody].dSeasDeltat;
  dt_Lf = body[iBody].dSeasDeltat/body[iBody].dLatentHeatIce;

  for (i=0;i<body[iBody].iNumLats+1;i++) {
    body[iBody].daLambdaSea[i] = body[iBody].daDiffusionSea[i]*(1.0-(body[iBody].daXBoundary[i]*body[iBody].daXBoundary[i]))/((body[iBody].dSeasDeltax*body[iBody].dSeasDeltax));
  }

  for (i=0;i<body[iBody].iNumLats;i++) {
    nu_fl = body[iBody].dNuLandWater/body[iBody].daLandFrac[i];
    nu_fw = body[iBody].dNuLandWater/body[iBody].daWaterFrac[i];
    for (j=0;j<body[iBody].iNumLats;j++) {
      if (j==i) {
        body[iBody].daMDiffSea[i][j] = (-body[iBody].daLambdaSea[i+1]-body[iBody].daLambdaSea[i]);
        if (body[iBody].bAccuracyMode) {
          body[iBody].daMLand[i][j] = Cl_dt+body[iBody].daPlanckBSea[i]+nu_fl-body[iBody].daMDiffSea[i][j];
          body[iBody].daMWater[i][j] = Cw_dt+body[iBody].daPlanckBSea[i]+nu_fw-body[iBody].daMDiffSea[i][j];
        } else {
          body[iBody].daMLand[i][j] = Cl_dt+body[iBody].daPlanckBAvg[i]+nu_fl-body[iBody].daMDiffSea[i][j];
          body[iBody].daMWater[i][j] = Cw_dt+body[iBody].daPlanckBAvg[i]+nu_fw-body[iBody].daMDiffSea[i][j];
        }
      } else if (j==(i+1)) {
        body[iBody].daMDiffSea[i][j] = body[iBody].daLambdaSea[j];
        body[iBody].daMLand[i][j] = -body[iBody].daLambdaSea[j];
        body[iBody].daMWater[i][j] = -body[iBody].daLambdaSea[j];
      } else if (j==(i-1)) {
        body[iBody].daMDiffSea[i][j] = body[iBody].daLambdaSea[i];
        body[iBody].daMLand[i][j] = -body[iBody].daLambdaSea[i];
        body[iBody].daMWater[i][j] = -body[iBody].daLambdaSea[i];
      } else {
        body[iBody].daMDiffSea[i][j] = 0.0;
        body[iBody].daMLand[i][j] = 0.0;
        body[iBody].daMWater[i][j] = 0.0;
      }
    }
    body[iBody].daMInit[2*i][2*i+1] = -1*nu_fl;
    body[iBody].daMInit[2*i+1][2*i] = -1*nu_fw;

    for (j=0;j<body[iBody].iNumLats;j++) {
      body[iBody].daMInit[2*i][2*j] = body[iBody].daMLand[i][j];
      body[iBody].daMInit[2*i+1][2*j+1] = body[iBody].daMWater[i][j];
    }
  }

  for (i=0;i<2*body[iBody].iNumLats;i++) {
    for (j=0;j<2*body[iBody].iNumLats;j++) {
      body[iBody].daMEulerSea[i][j] = body[iBody].daMInit[i][j];
      body[iBody].daMEulerCopySea[i][j] = body[iBody].daMEulerCopySea[i][j];
    }
  }

  MatrixInvertSeasonal(body,iBody);
}

/**
Calculates non-matrix terms in the energy balance equation (I don't remember
why I called these "SourceF"). These terms are the OLR offset and the
absorbed radiation (temperature independent quantities).

@param body Struct containing all body information
@param iBody Body in question
@param day Day of the planet's year
*/
void SourceFSeas(BODY *body, int iBody, int day) {
  int i;

  for (i=0;i<body[iBody].iNumLats;i++) {
    body[iBody].daSourceL[i] = body[iBody].daPlanckASea[i] \
            - (1.0-body[iBody].daAlbedoLand[i])*body[iBody].daInsol[i][day];
    body[iBody].daSourceW[i] = body[iBody].daPlanckASea[i] \
            - (1.0-body[iBody].daAlbedoWater[i])*body[iBody].daInsol[i][day];
    body[iBody].daSourceLW[2*i] = body[iBody].daTempLand[i] * body[iBody].dHeatCapLand\
                  * body[iBody].dMeanMotion/(2*PI)/body[iBody].dSeasDeltat-body[iBody].daSourceL[i];
    body[iBody].daSourceLW[2*i+1] = body[iBody].daTempWater[i] * body[iBody].dHeatCapWater \
                  * body[iBody].dMeanMotion/(2*PI)/body[iBody].dSeasDeltat-body[iBody].daSourceW[i];
  }
}

/**
Calculates average energy residual or "error" over course of the year. This
should be used as a check on the physics in the EBM (should be ~0).

@param body Struct containing all body information
@param iBody Body in question
@param day Day of the planet's year
*/
void EnergyResiduals(BODY *body, int iBody, int day) {
  int i;
  double nu_fl, nu_fw, Cl_dt, Cw_dt, dt_Lf;
  Cl_dt = body[iBody].dHeatCapLand*body[iBody].dMeanMotion/(2*PI)/body[iBody].dSeasDeltat;
  Cw_dt = body[iBody].dHeatCapWater*body[iBody].dMeanMotion/(2*PI)/body[iBody].dSeasDeltat;
  dt_Lf = body[iBody].dSeasDeltat*body[iBody].dMeanMotion/(2*PI)/body[iBody].dLatentHeatIce;

  for (i=0;i<body[iBody].iNumLats;i++) {
    nu_fl = body[iBody].dNuLandWater/body[iBody].daLandFrac[i];
    nu_fw = body[iBody].dNuLandWater/body[iBody].daWaterFrac[i];

    if (i==0) {
      body[iBody].daEnergyResL[i] = body[iBody].daInsol[i][day]*\
        (1.0-body[iBody].daAlbedoLand[i])-Cl_dt*(body[iBody].daDeltaTempL[i])-\
        body[iBody].daLambdaSea[i+1]*(body[iBody].daTempLand[i]-body[iBody].daTempLand[i+1])-\
        nu_fl*(body[iBody].daTempLand[i]-body[iBody].daTempWater[i])-\
        body[iBody].daPlanckASea[i]-body[iBody].daPlanckBSea[i]*body[iBody].daTempLand[i];

      body[iBody].daEnergyResW[i] = body[iBody].daInsol[i][day]*\
        (1.0-body[iBody].daAlbedoWater[i])-Cw_dt*(body[iBody].daDeltaTempW[i])-\
        body[iBody].daLambdaSea[i+1]*(body[iBody].daTempWater[i]-body[iBody].daTempWater[i+1])-\
        nu_fw*(body[iBody].daTempWater[i]-body[iBody].daTempLand[i])-\
        body[iBody].daPlanckASea[i]-body[iBody].daPlanckBSea[i]*body[iBody].daTempWater[i];

    } else if (i==(body[iBody].iNumLats-1)) {
      body[iBody].daEnergyResL[i] = body[iBody].daInsol[i][day]*\
        (1.0-body[iBody].daAlbedoLand[i])-Cl_dt*(body[iBody].daDeltaTempL[i])-\
        body[iBody].daLambdaSea[i]*(body[iBody].daTempLand[i]-body[iBody].daTempLand[i-1])-\
        nu_fl*(body[iBody].daTempLand[i]-body[iBody].daTempWater[i])-\
        body[iBody].daPlanckASea[i]-body[iBody].daPlanckBSea[i]*body[iBody].daTempLand[i];

      body[iBody].daEnergyResW[i] = body[iBody].daInsol[i][day]*\
        (1.0-body[iBody].daAlbedoWater[i])-Cw_dt*(body[iBody].daDeltaTempW[i])-\
        body[iBody].daLambdaSea[i]*(body[iBody].daTempWater[i]-body[iBody].daTempWater[i-1])-\
        nu_fw*(body[iBody].daTempWater[i]-body[iBody].daTempLand[i])-\
        body[iBody].daPlanckASea[i]-body[iBody].daPlanckBSea[i]*body[iBody].daTempWater[i];
    } else {
      body[iBody].daEnergyResL[i] = body[iBody].daInsol[i][day]*\
        (1.0-body[iBody].daAlbedoLand[i])-Cl_dt*(body[iBody].daDeltaTempL[i])-\
        body[iBody].daLambdaSea[i]*(body[iBody].daTempLand[i]-body[iBody].daTempLand[i-1])-\
        body[iBody].daLambdaSea[i+1]*(body[iBody].daTempLand[i]-body[iBody].daTempLand[i+1])-\
        nu_fl*(body[iBody].daTempLand[i]-body[iBody].daTempWater[i])-\
        body[iBody].daPlanckASea[i]-body[iBody].daPlanckBSea[i]*body[iBody].daTempLand[i];

      body[iBody].daEnergyResW[i] = body[iBody].daInsol[i][day]*\
        (1.0-body[iBody].daAlbedoWater[i])-Cw_dt*(body[iBody].daDeltaTempW[i])-\
        body[iBody].daLambdaSea[i]*(body[iBody].daTempWater[i]-body[iBody].daTempWater[i-1])-\
        body[iBody].daLambdaSea[i+1]*(body[iBody].daTempWater[i]-body[iBody].daTempWater[i+1])-\
        nu_fw*(body[iBody].daTempWater[i]-body[iBody].daTempLand[i])-\
        body[iBody].daPlanckASea[i]-body[iBody].daPlanckBSea[i]*body[iBody].daTempWater[i];
    }

    body[iBody].daEnerResLAnn[i] += body[iBody].daEnergyResL[i]/body[iBody].iNStepInYear;
    body[iBody].daEnerResWAnn[i] += body[iBody].daEnergyResW[i]/body[iBody].iNStepInYear;
  }
}

/**
Runs the seasonal EBM, called from ForceBehavior. The seasonal EBM runs on a
fixed time-step (of order days) to resolve the seasonal cycle. It can be said
to be in "equilibrium" though not in "steady-state".

@param body Struct containing all body information and variables
@param iBody Body in question
*/
void PoiseSeasonal(BODY *body, int iBody) {
  int i, j, nstep, nyear, day;
  double h;

  h = 2*PI/body[iBody].dMeanMotion/body[iBody].iNStepInYear;

  //MatrixSeasonal(body,iBody);
  /* main loop */
  for (nyear=0;nyear<body[iBody].iNumYears;nyear++) {  //XXX confusing! Should distinguish b/w years/orbits
    body[iBody].dTGlobal = 0.0;
    body[iBody].dFluxInGlobal = 0.0;
    body[iBody].dFluxOutGlobal = 0.0;

    for (i=0;i<body[iBody].iNumLats;i++) {
        //start of year, reset annual averages to zero
        body[iBody].daTempAvg[i] = 0.0;
        body[iBody].daPlanckBAvg[i] = 0.0;
        body[iBody].daAlbedoAvg[i] = 0.0;
        body[iBody].daTempAvgL[i] = 0.0;
        body[iBody].daTempAvgW[i] = 0.0;
        body[iBody].daAlbedoAvgL[i] = 0.0;
        body[iBody].daAlbedoAvgW[i] = 0.0;
        body[iBody].daFluxAvg[i] = 0.0;
        body[iBody].daFluxInAvg[i] = 0.0;
        body[iBody].daDivFluxAvg[i] = 0.0;
        body[iBody].daFluxOutAvg[i] = 0.0;
        body[iBody].daIceBalanceAnnual[i] = 0.0;
        body[iBody].daEnerResLAnn[i] = 0.0;
        body[iBody].daEnerResWAnn[i] = 0.0;
        body[iBody].daTempMinLW[i] = dHUGE;
        body[iBody].daTempMaxLW[i] = -1*dHUGE;
        body[iBody].daTempMaxLand[i] = -1*dHUGE;
        body[iBody].daTempMaxWater[i] = -1*dHUGE;

        if (nyear == 0) {
          //reset ice sheet stuff only on first year
          if (body[iBody].bIceSheets) {
            body[iBody].daIceMassTmp[i] = body[iBody].daIceMass[i];
            body[iBody].daIceAccumTot[i] = 0;
            body[iBody].daIceAblateTot[i] = 0;
          }
        }
    }

    AlbedoSeasonal(body,iBody,0);
    body[iBody].dAlbedoGlobal = 0.0;

    for (nstep=0;nstep<body[iBody].iNStepInYear;nstep++) {
      body[iBody].dTGlobalTmp = 0.0;
      body[iBody].dFluxInGlobalTmp = 0.0;
      body[iBody].dFluxOutGlobalTmp = 0.0;
      day = floor(body[iBody].dSeasDeltat*nstep*body[iBody].iNDays);

      SourceFSeas(body, iBody, day);

      if (body[iBody].bSeaIceModel == 1) {
        SeaIce(body,iBody);
        for (i=0;i<body[iBody].iNumLats;i++) {
          if (body[iBody].daSeaIceHeight[i] > 0) {
            // adjust height of present sea ice
            body[iBody].daSeaIceHeight[i] -=body[iBody].dSeasDeltat/body[iBody].dLatentHeatIce\
                                       * body[iBody].daFluxSeaIce[i];
            if (body[iBody].daSeaIceHeight[i] < 0) body[iBody].daSeaIceHeight[i] = 0;
          } else {
            if (body[iBody].daTempWater[i] < body[iBody].dFrzTSeaIce) {
              // create new sea ice
              body[iBody].daSeaIceHeight[i] = \
                    -body[iBody].dHeatCapWater*body[iBody].dMeanMotion/(2*PI)\
                    /body[iBody].dLatentHeatIce*(body[iBody].daTempWater[i] - body[iBody].dFrzTSeaIce);
            }
          }

          Snowball(body,iBody);
          // ice growth/ablation
          if (body[iBody].bIceSheets) {
            //calculate derivative of ice mass density and take an euler step
            body[iBody].daIceBalance[i][nstep] = IceMassBalance(body,iBody,i);
            body[iBody].daIceMassTmp[i] += h*body[iBody].daIceBalance[i][nstep];
            if (body[iBody].daIceBalance[i][nstep] >= 0) {
              body[iBody].daIceAccumTot[i] += h*body[iBody].daIceBalance[i][nstep]/body[iBody].iNumYears;
            } else {
              if (body[iBody].daIceMassTmp[i] > 0) {
                if (body[iBody].daIceMassTmp[i] >= h*body[iBody].daIceBalance[i][nstep]) {
                  body[iBody].daIceAblateTot[i] += h*body[iBody].daIceBalance[i][nstep]/body[iBody].iNumYears;
                } else {
                  body[iBody].daIceAblateTot[i] += body[iBody].daIceMassTmp[i];
                }
              }
            }
            if (body[iBody].daIceMassTmp[i] < 0.0) {
               body[iBody].daIceMassTmp[i] = 0.0;
            } //don't let ice mass become negative
            if (body[iBody].daIceBalance[i][nstep] < 0 && body[iBody].daIceMassTmp[i] != 0) {
              if (body[iBody].daIceMassTmp[i] <= fabs(h*body[iBody].daIceBalance[i][nstep])) {
                body[iBody].daTempLand[i] += -body[iBody].daIceMassTmp[i]*LFICE/\
                    body[iBody].dHeatCapLand; //adjust temperature
              } else {
                body[iBody].daTempLand[i] += h*body[iBody].daIceBalance[i][nstep]*LFICE/\
                  body[iBody].dHeatCapLand; //adjust temperature
              }
            } else if (body[iBody].daIceBalance[i][nstep] > 0) {
              body[iBody].daTempLand[i] += h*body[iBody].daIceBalance[i][nstep]*LFICE/\
                  body[iBody].dHeatCapLand; //adjust temperature
            }
          }

          body[iBody].daTempLW[i] = body[iBody].daLandFrac[i]*body[iBody].daTempLand[i] + \
                            body[iBody].daWaterFrac[i]*body[iBody].daTempWater[i];
          body[iBody].dTGlobalTmp += body[iBody].daTempLW[i]/body[iBody].iNumLats;

          if (body[iBody].bCalcAB) {
            if (body[iBody].iOLRModel == WK97) {
              /* Calculate A and B from williams and kasting 97 result */
              body[iBody].daPlanckBSea[i] = dOLRdTwk97(body,iBody,i,SEA);
              body[iBody].daPlanckASea[i] = OLRwk97(body,iBody,i,SEA) \
                 - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
            } else if (body[iBody].iOLRModel == HM16) {
              /* Calculate A and B from haqq-misra+ 2016 result */
              body[iBody].daPlanckBSea[i] = dOLRdThm16(body,iBody,i,SEA);
              body[iBody].daPlanckASea[i] = OLRhm16(body,iBody,i,SEA) \
                - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
            } else {
              /* Calculate A and B from spiegel+ 2009 model */
              body[iBody].daPlanckBSea[i] = dOLRdTsms09(body,iBody,i,SEA);
              body[iBody].daPlanckASea[i] = OLRsms09(body,iBody,i,SEA) \
                - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
            }


            if (body[iBody].bMEPDiff) {
              if (i==0) {
                body[iBody].daDiffusionSea[i] = body[iBody].daPlanckBSea[i]/4.0;
              } else if (i==(body[iBody].iNumLats-1)) {
                body[iBody].daDiffusionSea[i] = (body[iBody].daPlanckBSea[i]+body[iBody].daPlanckBSea[i-1])/8.0;
                body[iBody].daDiffusionSea[i+1] = body[iBody].daPlanckBSea[i]/4.0;
              } else {
                body[iBody].daDiffusionSea[i] = (body[iBody].daPlanckBSea[i]+body[iBody].daPlanckBSea[i-1])/8.0;
              }
            }
          }

          //calculate fluxes by latitude and global average
          body[iBody].daFluxOutLand[i] = body[iBody].daPlanckASea[i] \
                                  + body[iBody].daPlanckBSea[i]*body[iBody].daTempLand[i];
          body[iBody].daFluxOutWater[i] = body[iBody].daPlanckASea[i] \
                                  + body[iBody].daPlanckBSea[i]*body[iBody].daTempWater[i];
          body[iBody].daFluxOut[i] = body[iBody].daLandFrac[i]*body[iBody].daFluxOutLand[i] + \
                                  body[iBody].daWaterFrac[i]*body[iBody].daFluxOutWater[i];
          body[iBody].dFluxOutGlobalTmp += body[iBody].daFluxOut[i]/body[iBody].iNumLats;

          body[iBody].daFluxInLand[i] = (1.0-body[iBody].daAlbedoLand[i])\
                                          *body[iBody].daInsol[i][day];
          body[iBody].daFluxInWater[i] = (1.0-body[iBody].daAlbedoWater[i])\
                                          *body[iBody].daInsol[i][day];
          body[iBody].daFluxIn[i] = body[iBody].daLandFrac[i]*body[iBody].daFluxInLand[i] + \
                                  body[iBody].daWaterFrac[i]*body[iBody].daFluxInWater[i];
          body[iBody].dFluxInGlobalTmp += body[iBody].daFluxIn[i]/body[iBody].iNumLats;

          // annual averages by latitude
          body[iBody].daTempAvg[i] += body[iBody].daTempLW[i]/body[iBody].iNStepInYear;
          body[iBody].daPlanckBAvg[i] += body[iBody].daPlanckBSea[i]/body[iBody].iNStepInYear;
          body[iBody].daAlbedoAvg[i] += body[iBody].daAlbedoLW[i]/body[iBody].iNStepInYear;
          body[iBody].daFluxInAvg[i] += body[iBody].daFluxIn[i]/body[iBody].iNStepInYear;
          body[iBody].daFluxOutAvg[i] += body[iBody].daFluxOut[i]/body[iBody].iNStepInYear;
          body[iBody].daTempDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daTempLW[i];
          body[iBody].daTempAvgL[i] += body[iBody].daTempLand[i]/body[iBody].iNStepInYear;
          body[iBody].daTempAvgW[i] += body[iBody].daTempWater[i]/body[iBody].iNStepInYear;
          body[iBody].daAlbedoAvgL[i] += body[iBody].daAlbedoLand[i]/body[iBody].iNStepInYear;
          body[iBody].daAlbedoAvgW[i] += body[iBody].daAlbedoWater[i]/body[iBody].iNStepInYear;
          body[iBody].daAlbedoAvg[i] += body[iBody].daAlbedoLW[i]/body[iBody].iNStepInYear;
          body[iBody].daFluxInAvg[i] += body[iBody].daFluxIn[i]/body[iBody].iNStepInYear;
          body[iBody].daFluxOutAvg[i] += body[iBody].daFluxOut[i]/body[iBody].iNStepInYear;

          // daily values for output over year
          body[iBody].daTempDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daTempLW[i];
          body[iBody].daFluxInDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daFluxIn[i];
          body[iBody].daFluxOutDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daFluxOut[i];
          body[iBody].daPlanckBDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daPlanckBSea[i];
          if (body[iBody].daTempLW[i] < body[iBody].daTempMinLW[i])
            body[iBody].daTempMinLW[i] = body[iBody].daTempLW[i];
          if (body[iBody].daTempLW[i] > body[iBody].daTempMaxLW[i])
            body[iBody].daTempMaxLW[i] = body[iBody].daTempLW[i];
          if (body[iBody].daTempLand[i] > body[iBody].daTempMaxLand[i])
            body[iBody].daTempMaxLand[i] = body[iBody].daTempLand[i];
          if (body[iBody].daTempWater[i] > body[iBody].daTempMaxWater[i])
            body[iBody].daTempMaxWater[i] = body[iBody].daTempWater[i];
        }

        TempGradientSea(body, body[iBody].dSeasDeltax, iBody);
        for (i=0;i<body[iBody].iNumLats;i++) {
          body[iBody].daDMidPt[i] = 0.5*(body[iBody].daDiffusionSea[i+1]+body[iBody].daDiffusionSea[i]);
          body[iBody].daFlux[i] = -2.*PI*(body[iBody].dRadius*body[iBody].dRadius)*sqrt(1.0-(sin(body[iBody].daLats[i])*sin(body[iBody].daLats[i]))) * \
                            body[iBody].daDMidPt[i]*body[iBody].daTGrad[i];
          body[iBody].daFluxAvg[i] += body[iBody].daFlux[i]/body[iBody].iNStepInYear;
          body[iBody].daFluxDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daFlux[i];

          body[iBody].daDivFlux[i] = 0.0;
          for (j=0;j<body[iBody].iNumLats;j++) {
            body[iBody].daDivFlux[i] += -body[iBody].daMDiffSea[i][j]*body[iBody].daTempLW[j];
          }
          body[iBody].daDivFluxAvg[i] += body[iBody].daDivFlux[i]/body[iBody].iNStepInYear;
          body[iBody].daDivFluxDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daDivFlux[i];
        }

        body[iBody].dTGlobal += \
          body[iBody].dTGlobalTmp/(body[iBody].iNStepInYear);
        body[iBody].dFluxOutGlobal += \
              body[iBody].dFluxOutGlobalTmp/(body[iBody].iNStepInYear);
        body[iBody].dFluxInGlobal += \
              body[iBody].dFluxInGlobalTmp/(body[iBody].iNStepInYear);

      } else {
        for (i=0;i<2*body[iBody].iNumLats;i++) {
          body[iBody].daTmpTempSea[i] = 0.0;
          for (j=0;j<2*body[iBody].iNumLats;j++) {
            body[iBody].daTmpTempSea[i] += body[iBody].daInvMSea[i][j]*body[iBody].daSourceLW[j];
          }
        }
        for (i=0;i<body[iBody].iNumLats;i++) {
          //temp change this time step
          body[iBody].daDeltaTempL[i] = body[iBody].daTmpTempSea[2*i]-body[iBody].daTempLand[i];
          body[iBody].daDeltaTempW[i] = body[iBody].daTmpTempSea[2*i+1]-body[iBody].daTempWater[i];
          //calculate temperature and fluxes by latitude and global average
          body[iBody].daTempLand[i] = body[iBody].daTmpTempSea[2*i];
          body[iBody].daTempWater[i] = body[iBody].daTmpTempSea[2*i+1];

          Snowball(body,iBody);
          // ice growth/ablation
          if (body[iBody].bIceSheets) {
            //calculate derivative of ice mass density and take an euler step
            body[iBody].daIceBalance[i][nstep] = IceMassBalance(body,iBody,i);
            body[iBody].daIceMassTmp[i] += h*body[iBody].daIceBalance[i][nstep];
//             if (i==0) printf("nstep = %d, ice mass 0 = %f\n",nstep,body[iBody].daIceMassTmp[i]);
            if (body[iBody].daIceBalance[i][nstep] >= 0) {
              body[iBody].daIceAccumTot[i] += h*body[iBody].daIceBalance[i][nstep]/body[iBody].iNumYears;
            } else {
              if (body[iBody].daIceMassTmp[i] > 0) {
                if (body[iBody].daIceMassTmp[i] >= h*body[iBody].daIceBalance[i][nstep]) {
                  body[iBody].daIceAblateTot[i] += h*body[iBody].daIceBalance[i][nstep]/body[iBody].iNumYears;
                } else {
                  body[iBody].daIceAblateTot[i] += body[iBody].daIceMassTmp[i];
                }
              }
            }
            if (body[iBody].daIceMassTmp[i] < 0.0) {
               body[iBody].daIceMassTmp[i] = 0.0;
            } //don't let ice mass become negative
            if (body[iBody].daIceBalance[i][nstep] < 0 && body[iBody].daIceMassTmp[i] != 0) {
              if (body[iBody].daIceMassTmp[i] <= fabs(h*body[iBody].daIceBalance[i][nstep])) {
                body[iBody].daTempLand[i] += -body[iBody].daIceMassTmp[i]*LFICE/\
                    body[iBody].dHeatCapLand; //adjust temperature
              } else {
                body[iBody].daTempLand[i] += h*body[iBody].daIceBalance[i][nstep]*LFICE/\
                  body[iBody].dHeatCapLand; //adjust temperature
              }
            } else if (body[iBody].daIceBalance[i][nstep] > 0) {
              body[iBody].daTempLand[i] += h*body[iBody].daIceBalance[i][nstep]*LFICE/\
                  body[iBody].dHeatCapLand; //adjust temperature
            }
          }

          body[iBody].daTempLW[i] = body[iBody].daLandFrac[i]*body[iBody].daTempLand[i] + \
                                  body[iBody].daWaterFrac[i]*body[iBody].daTempWater[i];
          body[iBody].dTGlobalTmp += body[iBody].daTempLW[i]/body[iBody].iNumLats;

          if (body[iBody].bCalcAB) {
            if (body[iBody].iOLRModel == WK97) {
              body[iBody].daPlanckBSea[i] = dOLRdTwk97(body,iBody,i,SEA);
              body[iBody].daPlanckASea[i] = OLRwk97(body,iBody,i,SEA) \
                    - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
            } else if (body[iBody].iOLRModel == HM16) {
              /* Calculate A and B from haqq-misra+ 2016 result */
              body[iBody].daPlanckBSea[i] = dOLRdThm16(body,iBody,i,SEA);
              body[iBody].daPlanckASea[i] = OLRhm16(body,iBody,i,SEA) \
                - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
            } else {
              /* Calculate A and B from spiegel+ 2009 model */
              body[iBody].daPlanckBSea[i] = dOLRdTsms09(body,iBody,i,SEA);
              body[iBody].daPlanckASea[i] = OLRsms09(body,iBody,i,SEA) \
                - body[iBody].daPlanckBSea[i]*(body[iBody].daTempLW[i]);
            }

            if (body[iBody].bMEPDiff) {
              if (i==0) {
                body[iBody].daDiffusionSea[i] = body[iBody].daPlanckBSea[i]/4.0;
              } else if (i==(body[iBody].iNumLats-1)) {
                body[iBody].daDiffusionSea[i] = (body[iBody].daPlanckBSea[i]+body[iBody].daPlanckBSea[i-1])/8.0;
                body[iBody].daDiffusionSea[i+1] = body[iBody].daPlanckBSea[i]/4.0;
              } else {
                body[iBody].daDiffusionSea[i] = (body[iBody].daPlanckBSea[i]+body[iBody].daPlanckBSea[i-1])/8.0;
              }
            }
          }

          body[iBody].daFluxOutLand[i] = body[iBody].daPlanckASea[i] \
                                  + body[iBody].daPlanckBSea[i]*body[iBody].daTempLand[i];
          body[iBody].daFluxOutWater[i] = body[iBody].daPlanckASea[i] \
                                  + body[iBody].daPlanckBSea[i]*body[iBody].daTempWater[i];
          body[iBody].daFluxOut[i] = body[iBody].daLandFrac[i]*body[iBody].daFluxOutLand[i] + \
                                  body[iBody].daWaterFrac[i]*body[iBody].daFluxOutWater[i];
          body[iBody].dFluxOutGlobalTmp += body[iBody].daFluxOut[i]/body[iBody].iNumLats;

          body[iBody].daFluxInLand[i] = (1.0-body[iBody].daAlbedoLand[i])\
                                          *body[iBody].daInsol[i][day];
          body[iBody].daFluxInWater[i] = (1.0-body[iBody].daAlbedoWater[i])\
                                          *body[iBody].daInsol[i][day];
          body[iBody].daFluxIn[i] = body[iBody].daLandFrac[i]*body[iBody].daFluxInLand[i] + \
                                  body[iBody].daWaterFrac[i]*body[iBody].daFluxInWater[i];
          body[iBody].dFluxInGlobalTmp += body[iBody].daFluxIn[i]/body[iBody].iNumLats;

          // annual averages by latitude
          body[iBody].daTempAvg[i] += body[iBody].daTempLW[i]/body[iBody].iNStepInYear;
          body[iBody].daPlanckBAvg[i] += body[iBody].daPlanckBSea[i]/body[iBody].iNStepInYear;
          body[iBody].daTempAvgL[i] += body[iBody].daTempLand[i]/body[iBody].iNStepInYear;
          body[iBody].daTempAvgW[i] += body[iBody].daTempWater[i]/body[iBody].iNStepInYear;
          body[iBody].daAlbedoAvgL[i] += body[iBody].daAlbedoLand[i]/body[iBody].iNStepInYear;
          body[iBody].daAlbedoAvgW[i] += body[iBody].daAlbedoWater[i]/body[iBody].iNStepInYear;
          body[iBody].daAlbedoAvg[i] += body[iBody].daAlbedoLW[i]/body[iBody].iNStepInYear;
          body[iBody].daFluxInAvg[i] += body[iBody].daFluxIn[i]/body[iBody].iNStepInYear;
          body[iBody].daFluxOutAvg[i] += body[iBody].daFluxOut[i]/body[iBody].iNStepInYear;

          body[iBody].daTempDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daTempLW[i];
          body[iBody].daFluxInDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daFluxIn[i];
          body[iBody].daFluxOutDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daFluxOut[i];
          body[iBody].daPlanckBDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daPlanckBSea[i];
          if (body[iBody].daTempLW[i] < body[iBody].daTempMinLW[i])
            body[iBody].daTempMinLW[i] = body[iBody].daTempLW[i];
          if (body[iBody].daTempLW[i] > body[iBody].daTempMaxLW[i])
            body[iBody].daTempMaxLW[i] = body[iBody].daTempLW[i];
          if (body[iBody].daTempLand[i] > body[iBody].daTempMaxLand[i])
            body[iBody].daTempMaxLand[i] = body[iBody].daTempLand[i];
          if (body[iBody].daTempWater[i] > body[iBody].daTempMaxWater[i])
            body[iBody].daTempMaxWater[i] = body[iBody].daTempWater[i];
        }

        TempGradientSea(body, body[iBody].dSeasDeltax, iBody);
        for (i=0;i<body[iBody].iNumLats;i++) {
          body[iBody].daDMidPt[i] = 0.5*(body[iBody].daDiffusionSea[i+1]+body[iBody].daDiffusionSea[i]);
          body[iBody].daFlux[i] = -2.*PI*(body[iBody].dRadius*body[iBody].dRadius)*sqrt(1.0-(sin(body[iBody].daLats[i])*sin(body[iBody].daLats[i]))) * \
                            body[iBody].daDMidPt[i]*body[iBody].daTGrad[i];
          body[iBody].daFluxAvg[i] += body[iBody].daFlux[i]/body[iBody].iNStepInYear;
          body[iBody].daFluxDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daFlux[i];

          body[iBody].daDivFlux[i] = 0.0;
          for (j=0;j<body[iBody].iNumLats;j++) {
            body[iBody].daDivFlux[i] += -body[iBody].daMDiffSea[i][j]*body[iBody].daTempLW[j];
          }
          body[iBody].daDivFluxAvg[i] += body[iBody].daDivFlux[i]/body[iBody].iNStepInYear;
          body[iBody].daDivFluxDaily[i][nyear*body[iBody].iNStepInYear+nstep] = body[iBody].daDivFlux[i];
        }

        body[iBody].dTGlobal += \
              body[iBody].dTGlobalTmp/(body[iBody].iNStepInYear);
        body[iBody].dFluxOutGlobal += \
              body[iBody].dFluxOutGlobalTmp/(body[iBody].iNStepInYear);
        body[iBody].dFluxInGlobal += \
              body[iBody].dFluxInGlobalTmp/(body[iBody].iNStepInYear);

      }

      EnergyResiduals(body,iBody,day);
      AlbedoSeasonal(body,iBody,day);
      if (body[iBody].bAccuracyMode) {
        MatrixSeasonal(body,iBody);
      }
    }

    if (body[iBody].bIceSheets) {
      for (i=0;i<body[iBody].iNumLats;i++) {
        if (nyear != 0) {
          body[iBody].daIceBalanceAnnual[i] += h/2.*(body[iBody].daIceBalance[i][0])/ \
                         (body[iBody].iNumYears*2*PI/body[iBody].dMeanMotion);
        }
        for (nstep=1;nstep<body[iBody].iNStepInYear;nstep++) {
          //trapezoid rule
          //h = 2*PI/body[iBody].dMeanMotion/body[iBody].iNStepInYear;
          body[iBody].daIceBalanceAnnual[i] += h/2.*(body[iBody].daIceBalance[i][nstep]\
                         + body[iBody].daIceBalance[i][nstep-1])/ \
                         (body[iBody].iNumYears*2*PI/body[iBody].dMeanMotion);
          //above gets yearly average over NumYears
        }
        if (nyear != (body[iBody].iNumYears-1)) {
          body[iBody].daIceBalanceAnnual[i] += h/2.*(body[iBody].daIceBalance[i][nstep-1])/ \
                         (body[iBody].iNumYears*2*PI/body[iBody].dMeanMotion);
        }
      }
    }
  }
}

/**
Calculates the net balance between melting and accumulation of ice on land
at a given EBM time-step

@param body Struct containing all body information
@param iBody Body in question
@param iLat Latitude cell in question
@return Net gain/loss of ice
*/
double IceMassBalance(BODY *body, int iBody, int iLat) {
  double Tice = 273.15, dTmp, dh, dGamma, dTs;

  if (body[iBody].bElevFB) {
    //elevation feedback modeled by assuming surface temp is affected by height
    //Very experimental!
    dGamma = body[iBody].dLapseR; //dry adiabatic lapse rate
    dh = (body[iBody].daIceMassTmp[iLat]/RHOICE - body[iBody].dRefHeight+body[iBody].daBedrockH[iLat]);  //height above or below some ref altitude
    dTs = (body[iBody].daTempLand[iLat]+273.15-dGamma*dh);  //''surface'' temperature of ice
  } else {
    dTs = body[iBody].daTempLand[iLat]+273.15;
  }
  /* first, calculate melting/accumulation */
  if (dTs>273.15) {
    /* Ice melting */
    /* (AblateFF is used to match Huybers&Tziperman's ablation rate)*/
    dTmp = body[iBody].dAblateFF*SIGMA*((Tice*Tice*Tice*Tice) - \
        ((dTs)*(dTs)*(dTs)*(dTs)))/LFICE;
  } else {
    if (body[iBody].bSnowball) {
      /* no precip once planet is frozen */
      dTmp = 0.0;
    } else {
      if (body[iBody].dIceMassTot >= MOCEAN) {
        /* ice growth limited by mass of water available (really, really stupid) */
        dTmp = 0.0;
      } else {
        /* Ice deposits at fixed rate */
        dTmp = body[iBody].dIceDepRate;
      }
    }
  }
  return dTmp;
}

/**
Construct matrix that evolves the ice sheet flow + net balance

@param body Struct containing body information
@param iBody Body in question
*/
void IceSheetTriDiag(BODY *body, int iBody) {
  double bTmp;
  int i, n = body[iBody].iNumLats;

  bTmp = body[iBody].daIceSheetMat[0][0];
  body[iBody].daIceHeight[0] = body[iBody].daIcePropsTmp[0]/bTmp;
  for (i=1;i<n;i++) {
    body[iBody].daIceGamTmp[i] = body[iBody].daIceSheetMat[i-1][i]/bTmp;
    bTmp = body[iBody].daIceSheetMat[i][i]-body[iBody].daIceSheetMat[i][i-1]*body[iBody].daIceGamTmp[i];
    if (bTmp == 0) {
      fprintf(stderr,"Ice sheet tri-diagonal solution failed\n");
      exit(EXIT_INPUT);
    }
    body[iBody].daIceHeight[i] = (body[iBody].daIcePropsTmp[i]-body[iBody].daIceSheetMat[i][i-1]*\
      body[iBody].daIceHeight[i-1])/bTmp;
  }
  for (i=1;i<n;i++) {
    body[iBody].daIceHeight[n-i-1] -= body[iBody].daIceGamTmp[n-i]*body[iBody].daIceHeight[n-i];
  }
}

/**
Main ice sheet routine. Integrates the ice sheets via Crank-Nicholson method in
ForceBehavior in the same fashion as Huybers' model.

@param body Struct containing body information
@param evolve Struct containing evolution information
@param iBody Body in question
*/
void PoiseIceSheets(BODY *body, EVOLVE *evolve, int iBody) {
  /* integrate ice sheets via Crank-Nicholson method in ForceBehavior
     in the same way Huybers' model works */
  int iLat, jLat, skip = 1;
  double IceTime = evolve->dTime, IceDt, RunSeasNext;
  double deltax, Tice = 270, Aice, grav, dHdt;

  grav = BIGG*body[iBody].dMass/(body[iBody].dRadius*body[iBody].dRadius);
  /* deformability of ice, dependent on temperature */
  if (Tice < 263) {
    Aice = a1ICE * exp(-Q1ICE/(RGAS*Tice));
  } else {
    Aice = a2ICE * exp(-Q2ICE/(RGAS*Tice));
  }

  for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
    if (body[iBody].daIceMass[iLat] < 1e-30) {
      body[iBody].daIceMass[iLat] = 0.0;
    }
    body[iBody].daIceHeight[iLat] = body[iBody].daIceMass[iLat]/RHOICE;
    body[iBody].daIceBalanceAvg[iLat] = 0.0;
    body[iBody].daIceFlowAvg[iLat] = 0.0;
    if (body[iBody].daIceMass[iLat] > 0 || body[iBody].daIceBalanceAnnual[iLat] > 0) {
      skip = 0;
    }
  }

  RunSeasNext = IceTime + body[iBody].iReRunSeas*2*PI/body[iBody].dMeanMotion;
  IceDt = body[iBody].iIceTimeStep*2*PI/body[iBody].dMeanMotion;

  if (body[iBody].iIceTimeStep > 1) {
    if (body[iBody].dTGlobal < 0) {
      /* tip toe into snowball state to prevent instability */
      IceDt = 2*PI/body[iBody].dMeanMotion;
    }
  }

  if (skip == 0) {
    while (IceTime < evolve->dTime+evolve->dCurrentDt) {
      if (IceTime+IceDt > evolve->dTime+evolve->dCurrentDt) {
        //ice time step carries past start of next RK time step
        IceDt = evolve->dTime+evolve->dCurrentDt-IceTime;
      }

      Snowball(body, iBody);
      /* first, get ice balances */
      for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
        if (body[iBody].daIceMass[iLat] <= 0 && body[iBody].daIceBalanceAnnual[iLat] < 0.0) {
          body[iBody].daIceBalanceTmp[iLat] = 0;
        } else if (body[iBody].dIceMassTot >= MOCEAN && body[iBody].daIceBalanceAnnual[iLat] > 0.0) {
          body[iBody].daIceBalanceTmp[iLat] = 0;
        } else {
          body[iBody].daIceBalanceTmp[iLat] = body[iBody].daIceBalanceAnnual[iLat]/RHOICE;
        }
        if (body[iBody].bSnowball == 1) {
          body[iBody].daIceBalanceTmp[iLat] = 0;
        }
      }

      deltax = 2.0/body[iBody].iNumLats;

      for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
        /* calculate derivative to 2nd order accuracy */
        if (iLat == 0) {
          body[iBody].daDIceHeightDy[iLat] = sqrt(1.0-(body[iBody].daXBoundary[iLat+1]*body[iBody].daXBoundary[iLat+1])) * \
              (body[iBody].daIceHeight[iLat+1]+body[iBody].daBedrockH[iLat+1]-\
              body[iBody].daIceHeight[iLat]-body[iBody].daBedrockH[iLat]) / \
              (body[iBody].dRadius*deltax);
        } else if (iLat == (body[iBody].iNumLats-1)) {
          body[iBody].daDIceHeightDy[iLat] = sqrt(1.0-(body[iBody].daXBoundary[iLat]*body[iBody].daXBoundary[iLat])) * \
              (body[iBody].daIceHeight[iLat]+body[iBody].daBedrockH[iLat]-\
              body[iBody].daIceHeight[iLat-1]-body[iBody].daBedrockH[iLat-1]) / \
              (body[iBody].dRadius*deltax);
        } else {
          body[iBody].daDIceHeightDy[iLat] = (sqrt(1.0-(body[iBody].daXBoundary[iLat+1]*body[iBody].daXBoundary[iLat+1])) *\
              (body[iBody].daIceHeight[iLat+1]+body[iBody].daBedrockH[iLat+1]-\
              body[iBody].daIceHeight[iLat]-body[iBody].daBedrockH[iLat]) / \
              (body[iBody].dRadius*deltax) + sqrt(1.0-(body[iBody].daXBoundary[iLat]*body[iBody].daXBoundary[iLat])) *\
              (body[iBody].daIceHeight[iLat]+body[iBody].daBedrockH[iLat]-\
              body[iBody].daIceHeight[iLat-1]-body[iBody].daBedrockH[iLat-1]) / \
              (body[iBody].dRadius*deltax) )/2.0;
        }

        body[iBody].daIceFlow[iLat] = 2*Aice*pow(RHOICE*grav,nGLEN)/(nGLEN+2.0) * \
            pow(fabs(body[iBody].daDIceHeightDy[iLat]),nGLEN-1) * \
            pow(body[iBody].daIceHeight[iLat]+body[iBody].daBedrockH[iLat],nGLEN+2);
        body[iBody].daSedShear[iLat] = RHOICE*grav*body[iBody].daIceHeight[iLat]*\
            body[iBody].daDIceHeightDy[iLat];
        body[iBody].daBasalFlow[iLat] = BasalFlow(body,iBody,iLat);
      }

      for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
        if (IceTime != evolve->dTime) {
          body[iBody].daIceSheetDiff[iLat] = -0.5*(body[iBody].daIceFlowMid[iLat]+\
            body[iBody].daBasalFlowMid[iLat]);
          if (iLat == body[iBody].iNumLats-1) {
            body[iBody].daIceSheetDiff[iLat+1] = -0.5*(body[iBody].daIceFlowMid[iLat+1]+\
              body[iBody].daBasalFlowMid[iLat+1]);
          }
        }

        if (iLat == 0) {
          body[iBody].daIceFlowMid[iLat] = 0;
          body[iBody].daBasalFlowMid[iLat] = 0;
        } else if (iLat == body[iBody].iNumLats-1) {
          body[iBody].daIceFlowMid[iLat] = (body[iBody].daIceFlow[iLat] + \
             body[iBody].daIceFlow[iLat-1])/2.0;
          body[iBody].daIceFlowMid[iLat+1] = 0;
          body[iBody].daBasalFlowMid[iLat] = (body[iBody].daBasalFlow[iLat] + \
             body[iBody].daBasalFlow[iLat-1])/2.0;
          body[iBody].daBasalFlowMid[iLat+1] = 0;
        } else {
          body[iBody].daIceFlowMid[iLat] = (body[iBody].daIceFlow[iLat] + \
             body[iBody].daIceFlow[iLat-1])/2.0;
          body[iBody].daBasalFlowMid[iLat] = (body[iBody].daBasalFlow[iLat] + \
             body[iBody].daBasalFlow[iLat-1])/2.0;
        }

        if (IceTime == evolve->dTime) {
          body[iBody].daIceSheetDiff[iLat] = body[iBody].daIceFlowMid[iLat];
          if (iLat == body[iBody].iNumLats-1) {
            body[iBody].daIceSheetDiff[iLat+1] = body[iBody].daIceFlowMid[iLat+1];
          }
          body[iBody].daIcePropsTmp[iLat] = body[iBody].daIceHeight[iLat] + \
            body[iBody].daIceBalanceTmp[iLat]*IceDt;
        } else {
          body[iBody].daIceSheetDiff[iLat] += 1.5*(body[iBody].daIceFlowMid[iLat]+ \
              body[iBody].daBasalFlowMid[iLat]);
          if (iLat == body[iBody].iNumLats-1) {
            body[iBody].daIceSheetDiff[iLat+1] += 1.5*(body[iBody].daIceFlowMid[iLat+1]+ \
              body[iBody].daBasalFlowMid[iLat+1]);
          }
        }
      }

      for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
        for (jLat=0;jLat<body[iBody].iNumLats;jLat++) {
          if (jLat == iLat) {
            body[iBody].daIceSheetMat[iLat][jLat] = 1.0+0.5*IceDt*\
              (body[iBody].daIceSheetDiff[iLat]/(body[iBody].daYBoundary[iLat]*body[iBody].daYBoundary[iLat])+\
              body[iBody].daIceSheetDiff[iLat+1]/(body[iBody].daYBoundary[iLat+1]*body[iBody].daYBoundary[iLat+1]));
          } else if (jLat == iLat+1) { //superdiagonal
            body[iBody].daIceSheetMat[iLat][jLat] = -0.5*IceDt*body[iBody].daIceSheetDiff[jLat]\
              /(body[iBody].daYBoundary[jLat]*body[iBody].daYBoundary[jLat]);
          } else if (jLat == iLat-1) { //subdiagonal
            body[iBody].daIceSheetMat[iLat][jLat] = -0.5*IceDt*body[iBody].daIceSheetDiff[iLat]\
              /(body[iBody].daYBoundary[iLat]*body[iBody].daYBoundary[iLat]);
          } else {
            body[iBody].daIceSheetMat[iLat][jLat] = 0.0;
          }
        }
        if (IceTime != evolve->dTime) {
          if (iLat == 0) {
            body[iBody].daIcePropsTmp[iLat] = body[iBody].daIceBalanceTmp[iLat]*IceDt + \
              (1-0.5*IceDt*(body[iBody].daIceSheetDiff[iLat+1]/(body[iBody].daYBoundary[iLat+1]*body[iBody].daYBoundary[iLat+1])))\
              *body[iBody].daIceHeight[iLat] + 0.5*IceDt*body[iBody].daIceSheetDiff[iLat+1]*\
              body[iBody].daIceHeight[iLat+1]/(body[iBody].daYBoundary[iLat+1]*body[iBody].daYBoundary[iLat+1]);
          } else if (iLat == body[iBody].iNumLats -1) {
            body[iBody].daIcePropsTmp[iLat] = body[iBody].daIceBalanceTmp[iLat]*IceDt + \
              (1-0.5*IceDt*(body[iBody].daIceSheetDiff[iLat]/(body[iBody].daYBoundary[iLat]*body[iBody].daYBoundary[iLat])))\
              *body[iBody].daIceHeight[iLat] + 0.5*IceDt*body[iBody].daIceSheetDiff[iLat]*\
              body[iBody].daIceHeight[iLat-1]/ (body[iBody].daYBoundary[iLat]*body[iBody].daYBoundary[iLat]);
          } else {
            body[iBody].daIcePropsTmp[iLat] = body[iBody].daIceBalanceTmp[iLat]*IceDt + \
              (1-0.5*IceDt*(body[iBody].daIceSheetDiff[iLat]/(body[iBody].daYBoundary[iLat]*body[iBody].daYBoundary[iLat]) + \
              body[iBody].daIceSheetDiff[iLat+1]/(body[iBody].daYBoundary[iLat+1]*body[iBody].daYBoundary[iLat+1])))*\
              body[iBody].daIceHeight[iLat] + 0.5*IceDt*body[iBody].daIceSheetDiff[iLat+1]*\
              body[iBody].daIceHeight[iLat+1]/(body[iBody].daYBoundary[iLat+1]*body[iBody].daYBoundary[iLat+1]) +\
              0.5*IceDt*body[iBody].daIceSheetDiff[iLat]*body[iBody].daIceHeight[iLat-1]/\
              (body[iBody].daYBoundary[iLat]*body[iBody].daYBoundary[iLat]);
          }
        }
      }

      IceSheetTriDiag(body,iBody);
      for (iLat=0;iLat<body[iBody].iNumLats;iLat++) {
        body[iBody].daIceMass[iLat] = body[iBody].daIceHeight[iLat]*RHOICE;
        if (body[iBody].daIceMass[iLat] < 1e-30) {
          body[iBody].daIceMass[iLat] = 0.0;
          body[iBody].daIceHeight[iLat] = 0.0;
        }
        body[iBody].daIceBalanceAvg[iLat] += body[iBody].daIceBalanceTmp[iLat]*IceDt/evolve->dCurrentDt;
        if (iLat == 0) {
          body[iBody].daIceFlowAvg[iLat] += body[iBody].daIceSheetDiff[iLat+1]*\
            (body[iBody].daIceHeight[iLat+1]-body[iBody].daIceHeight[iLat])/\
            (body[iBody].daYBoundary[iLat+1]*body[iBody].daYBoundary[iLat+1])*IceDt/evolve->dCurrentDt;
        } else if (iLat == body[iBody].iNumLats-1) {
          body[iBody].daIceFlowAvg[iLat] += -body[iBody].daIceSheetDiff[iLat]*\
            (body[iBody].daIceHeight[iLat]-body[iBody].daIceHeight[iLat-1])\
            /(body[iBody].daYBoundary[iLat]*body[iBody].daYBoundary[iLat])*IceDt/evolve->dCurrentDt;
        } else {
          body[iBody].daIceFlowAvg[iLat] += (body[iBody].daIceSheetDiff[iLat+1]*\
            (body[iBody].daIceHeight[iLat+1]-body[iBody].daIceHeight[iLat])/\
            (body[iBody].daYBoundary[iLat+1]*body[iBody].daYBoundary[iLat+1])-body[iBody].daIceSheetDiff[iLat]*\
            (body[iBody].daIceHeight[iLat]-body[iBody].daIceHeight[iLat-1])\
            /(body[iBody].daYBoundary[iLat]*body[iBody].daYBoundary[iLat]))*IceDt/evolve->dCurrentDt;
        }
        dHdt = 1./(BROCKTIME*YEARSEC) * (body[iBody].daBedrockHEq[iLat]-body[iBody].daBedrockH[iLat] - \
          RHOICE*body[iBody].daIceHeight[iLat]/RHOBROCK);
        body[iBody].daBedrockH[iLat] += dHdt*IceDt;
      }

      IceTime += IceDt;
      if (IceTime >= RunSeasNext) {
        /* rerun the seasonal model to make sure climate params don't get too out of whack */
        PoiseSeasonal(body, iBody);
        RunSeasNext += body[iBody].iReRunSeas*2*PI/body[iBody].dMeanMotion;
      }
    }
  }
}
