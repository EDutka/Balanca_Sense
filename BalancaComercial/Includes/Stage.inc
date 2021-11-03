/*
*******************************************************************
Aplicação.......: Extração de Dados de Importação/Exportação 
Desenvolvida por: Eduardo Dutka
Empresa.........: 
Criada em.......: 01/11/2021
Descrição.......: Neste script são criados os qvds do Stage com os dados "crus" ou sejam sem qualquer manipulação
	
    Origem dos arquivos Usados:
    	Exportação - https://balanca.economia.gov.br/balanca/bd/comexstat-bd/ncm/EXP_COMPLETA.zip
		Importação - https://balanca.economia.gov.br/balanca/bd/comexstat-bd/ncm/IMP_COMPLETA.zip



*******************************************************************
Manutenções

ID.............: 
Chamado........:
Quando.........: 
Por............: 
Alterações.....: 
*/

//==================================================================
// Aba Main
//==================================================================

SET ThousandSep='.';
SET DecimalSep=',';
SET MoneyThousandSep='.';
SET MoneyDecimalSep=',';
SET MoneyFormat='R$#.##0,00;-R$#.##0,00';
SET TimeFormat='hh:mm:ss';
SET DateFormat='DD/MM/YYYY';
SET TimestampFormat='DD/MM/YYYY hh:mm:ss[.fff]';
SET FirstWeekDay=6;
SET BrokenWeeks=1;
SET ReferenceDay=0;
SET FirstMonthOfYear=1;
SET CollationLocale='pt-BR';
SET CreateSearchIndexOnReload=1;
SET MonthNames='jan;fev;mar;abr;mai;jun;jul;ago;set;out;nov;dez';
SET LongMonthNames='janeiro;fevereiro;março;abril;maio;junho;julho;agosto;setembro;outubro;novembro;dezembro';
SET DayNames='seg;ter;qua;qui;sex;sáb;dom';
SET LongDayNames='segunda-feira;terça-feira;quarta-feira;quinta-feira;sexta-feira;sábado;domingo';
SET NumericalAbbreviation='3:k;6:M;9:G;12:T;15:P;18:E;21:Z;24:Y;-3:m;-6:μ;-9:n;-12:p;-15:f;-18:a;-21:z;-24:y';



//==================================================================
// Aba Variáveis
// Define as variáveis que serão usadas no script
//==================================================================

Set vArquivos = 'Arquivos';
Set vStage    = 'Stage';
//==================================================================


//==================================================================
// Aba Importação e Exportação
//==================================================================

//==================================================================
// EXP_COMPLETA - Base Completa dos dados de exportação
//==================================================================
[EXP_COMPLETA]:
LOAD
    CO_ANO,
    CO_MES,
    CO_NCM,
    CO_UNID,
    CO_PAIS,
    SG_UF_NCM,
    CO_VIA,
    CO_URF,
    QT_ESTAT,
    KG_LIQUIDO,
    VL_FOB
FROM [lib://$(vArquivos)/EXP_COMPLETA.csv]
(txt, codepage is 28591, embedded labels, delimiter is ';', msq);

//==================================================================
Store EXP_COMPLETA into [lib://$(vStage)/EXP_COMPLETA.qvd](QVD);
Drop Table EXP_COMPLETA;
//==================================================================

//==================================================================
// IMP_COMPLETA - Base Completa dos dados de Importação
//==================================================================
[IMP_COMPLETA]:
LOAD
    CO_ANO,
    CO_MES,
    CO_NCM,
    CO_UNID,
    CO_PAIS,
    SG_UF_NCM,
    CO_VIA,
    CO_URF,
    QT_ESTAT,
    KG_LIQUIDO,
    VL_FOB,
    VL_FRETE,
    VL_SEGURO
FROM [lib://$(vArquivos)/IMP_COMPLETA.csv]
(txt, codepage is 28591, embedded labels, delimiter is ';', msq);

//==================================================================
Store IMP_COMPLETA into [lib://$(vStage)/IMP_COMPLETA.qvd](QVD);
Drop Table IMP_COMPLETA;
//==================================================================


//==================================================================
// Aba Cadastrais
//==================================================================

//==================================================================
// NCM - Unidade Estatística da NCM
//==================================================================
[NCM]:
LOAD
    CO_NCM,
    NO_NCM_POR,
    CO_UNID,
    NO_UNID,
    SG_UNID
FROM [lib://$(vArquivos)/TABELAS_AUXILIARES.xlsx] (ooxml, embedded labels, table is [6]);

//==================================================================
Store NCM into [lib://$(vStage)/NCM.qvd](QVD);
Drop Table NCM;
//==================================================================


//==================================================================
// Países
//==================================================================
[PAIS]:
LOAD
    CO_PAIS,
    CO_PAIS_ISON3,
    CO_PAIS_ISOA3,
    NO_PAIS,
    NO_PAIS_ING,
    NO_PAIS_ESP
FROM [lib://$(vArquivos)/TABELAS_AUXILIARES.xlsx]
(ooxml, embedded labels, table is [10]);

//==================================================================
Store PAIS into [lib://$(vStage)/PAIS.qvd](QVD);
Drop Table PAIS;
//==================================================================


//==================================================================
// Blocos de Países
//==================================================================
[BLOCO]:
LOAD
    CO_PAIS,
    CO_BLOCO,
    NO_BLOCO,
    NO_BLOCO_ING,
    NO_BLOCO_ESP
FROM [lib://$(vArquivos)/TABELAS_AUXILIARES.xlsx]
(ooxml, embedded labels, table is [11]);

//==================================================================
Store BLOCO into [lib://$(vStage)/BLOCO.qvd](QVD);
Drop Table BLOCO;
//==================================================================


//==================================================================
// Unidades da Federação (Brasil)
//==================================================================
[UF]:
LOAD
    CO_UF,
    SG_UF,
    NO_UF,
    NO_REGIAO
FROM [lib://$(vArquivos)/TABELAS_AUXILIARES.xlsx]
(ooxml, embedded labels, table is [12]);

//==================================================================
Store UF into [lib://$(vStage)/UF.qvd](QVD);
Drop Table UF;
//==================================================================


//==================================================================
// VIA - Código e descrição da via (modal) de transporte
//==================================================================
[VIA]:
LOAD
    CO_VIA,
    NO_VIA
FROM [lib://$(vArquivos)/TABELAS_AUXILIARES.xlsx]
(ooxml, embedded labels, table is [14]);

//==================================================================
Store VIA into [lib://$(vStage)/VIA.qvd](QVD);
Drop Table VIA;
//==================================================================


//==================================================================
// URF - Código e descrição da Unidade da Receita Federal 
//==================================================================
[UN_RECEITA_FED]:
LOAD
    CO_URF,
    NO_URF
FROM [lib://$(vArquivos)/TABELAS_AUXILIARES.xlsx]
(ooxml, embedded labels, table is [15]);

//==================================================================
Store UN_RECEITA_FED into [lib://$(vStage)/UN_RECEITA_FED.qvd](QVD);
Drop Table UN_RECEITA_FED;
//==================================================================


//==================================================================
// CUCI - Classificação Uniforme para Comércio Internacional
//==================================================================
[CUCI]:
LOAD
    CO_NCM,
    NO_NCM_POR,
    CO_CUCI_ITEM,
    NO_CUCI_ITEM,
    CO_CUCI_SUB,
    NO_CUCI_SUB,
    CO_CUCI_GRUPO,
    NO_CUCI_GRUPO,
    CO_CUCI_DIVISAO,
    NO_CUCI_DIVISAO,
    CO_CUCI_SEC,
    NO_CUCI_SEC
FROM [lib://Arquivos/TABELAS_AUXILIARES.xlsx]
(ooxml, embedded labels, table is [2]);



//==================================================================
Store CUCI into [lib://$(vStage)/CUCI.qvd](QVD);
Drop Table CUCI;
//==================================================================