/*
*******************************************************************
Aplicação.......: Transformação de Dados de Importação/Exportação 
Desenvolvida por: Eduardo Dutka
Empresa.........: 
Criada em.......: 01/11/2021
Descrição.......: Neste script são efetuadas as transformações necessárias	    

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
SET CreateSearchIndexOnReload=0;
SET MonthNames='jan;fev;mar;abr;mai;jun;jul;ago;set;out;nov;dez';
SET LongMonthNames='janeiro;fevereiro;março;abril;maio;junho;julho;agosto;setembro;outubro;novembro;dezembro';
SET DayNames='seg;ter;qua;qui;sex;sáb;dom';
SET LongDayNames='segunda-feira;terça-feira;quarta-feira;quinta-feira;sexta-feira;sábado;domingo';
SET NumericalAbbreviation='3:k;6:M;9:G;12:T;15:P;18:E;21:Z;24:Y;-3:m;-6:μ;-9:n;-12:p;-15:f;-18:a;-21:z;-24:y';

//==================================================================
// Aba Variáveis
//==================================================================

//==================================================================
// Define as variáveis que serão usadas no script
//==================================================================

Set vStage            = 'Stage';
Set vTransformados    = 'Transformados';
//==================================================================


//==================================================================
// Aba MAPPING
//==================================================================


//==================================================================
// Blocos de Países
//==================================================================
[MAP_BLOCO]:
Mapping LOAD
    CO_PAIS,
    NO_BLOCO &'|'& NO_BLOCO_ING &'|'& NO_BLOCO_ESP
FROM [lib://$(vStage)/BLOCO.QVD](QVD);


//==================================================================
// Dados URF
//==================================================================
[MAP_URF]:
Mapping
LOAD
    CO_URF,
    NO_URF
FROM [lib://$(vStage)/UN_RECEITA_FED.QVD](QVD);



//==================================================================
// Dados dos Vias Modais
//==================================================================
[MAP_VIA]:
Mapping 
LOAD
    CO_VIA,
    NO_VIA
FROM [lib://$(vStage)/VIA.QVD](QVD);


//==================================================================
// Aba Cadastros
//==================================================================


//==================================================================
// Países
//==================================================================
[PAIS]:
Load 
	CO_PAIS							as [País - Código],
    CO_PAIS_ISON3					as [País - Cód. ISO N3],
    CO_PAIS_ISOA3					as [País - Cód. ISO A3],
    NO_PAIS							as [País - Nome],
    NO_PAIS_ING						as [País - Nome Inglês],
    NO_PAIS_ESP						as [País - Nome Espanhol],
    SubField(MAP_BLOCO,'|',1)		as [País - Bloco],
    SubField(MAP_BLOCO,'|',2)		as [País - Bloco Inglês],
    SubField(MAP_BLOCO,'|',3)		as [País - Bloco Espanhol];
LOAD
    CO_PAIS,
    CO_PAIS_ISON3,
    CO_PAIS_ISOA3,
    NO_PAIS,
    NO_PAIS_ING,
    NO_PAIS_ESP,
    ApplyMap('MAP_BLOCO', CO_PAIS)	as MAP_BLOCO
FROM [lib://$(vStage)/PAIS.qvd](QVD);

//==================================================================
Store PAIS into [lib://$(vTransformados)/PAIS.qvd](QVD);
Drop Table PAIS;
//==================================================================


//==================================================================
// Unidades da Federação (Brasil)
//==================================================================
[UF]:
LOAD
    CO_UF							as [UF - Código],
    SG_UF							as [UF - Sigla],
    NO_UF							as [UF - Nome],
    NO_REGIAO						as [UF - Região]
FROM [lib://$(vStage)/UF.QVD](QVD);

//==================================================================
Store UF into [lib://$(vTransformados)/UF.qvd](QVD);
Drop Table UF;
//==================================================================

[CUCI]:
LOAD
    CO_NCM							as [NCM - Código],
    NO_NCM_POR						as [NCM - Nome],
    CO_CUCI_ITEM					as [Classif. - Item],
    NO_CUCI_ITEM					as [Classif. - Desc. Item],
    CO_CUCI_SUB						as [Classif. - Cód. Subclasse],
    NO_CUCI_SUB						as [Classif. - Subclasse],
    CO_CUCI_GRUPO					as [Classif. - Cód. Grupo],
    NO_CUCI_GRUPO					as [Classif. - Grupo],
    CO_CUCI_DIVISAO					as [Classif. - Cód. Divisão],
    NO_CUCI_DIVISAO					as [Classif. - Divisão],
    CO_CUCI_SEC						as [Classif. - Cód. Seção],
    NO_CUCI_SEC						as [Classif. - Seção]
FROM [lib://$(vStage)/CUCI.qvd] (qvd);
//==================================================================
Store CUCI into [lib://$(vTransformados)/Classif_Uniforme_Com_Internacional.qvd](QVD);
Drop Table CUCI;
//==================================================================




//==================================================================
// Aba Balança
//==================================================================

//==================================================================
// Balança - Junta as Bases de exportação e importação
//==================================================================
BALANCA:
LOAD
    '1 - Exportação'						as [Balança - Tipo],
    '1'										as [FLG_EXPORTACAO],
    CO_ANO									as [Balança - Ano],
    CO_MES									as [Balança - Mês],
    MakeDate(CO_ANO,CO_MES,01)  			as DATA,
    MonthName(MakeDate(CO_ANO,CO_MES,01)) 	as [Balança - AnoMês],
    CO_ANO&CO_MES							as [Balança - Periodo],
    CO_NCM									as [NCM - Código],
    CO_UNID									as [Balança - Unidade],
    CO_PAIS									as [País - Código],
    SG_UF_NCM								as [UF - Sigla],
    CO_VIA									as [Via - Código],
    CO_URF									as [URF - Código],
    QT_ESTAT								as [Balança - Quantidade],
    KG_LIQUIDO								as [Balança - Peso Líquido],
    VL_FOB									as [Balança - Vl. FOB],
    ApplyMap('MAP_VIA', CO_VIA)				as [Balança - Via Modal],
    ApplyMap('MAP_URF', CO_URF)				as [Balança - URF Desc.]
FROM [lib://$(vStage)/EXP_COMPLETA.qvd] (qvd)
where CO_ANO >= 2017;

Concatenate (BALANCA)
LOAD
	'2 - Importação'						as [Balança - Tipo],
    '0'										as [FLG_EXPORTACAO],
    CO_ANO									as [Balança - Ano],
    CO_MES									as [Balança - Mês],
    MakeDate(CO_ANO,CO_MES,01)  			as DATA,
    MonthName(MakeDate(CO_ANO,CO_MES,01)) 	as [Balança - AnoMês],
    CO_ANO&CO_MES							as [Balança - Periodo],
    CO_NCM									as [NCM - Código],
    CO_UNID									as [Balança - Unidade],
    CO_PAIS									as [País - Código],
    SG_UF_NCM								as [UF - Sigla],
    CO_VIA									as [Via - Código],
    CO_URF									as [URF - Código],
    QT_ESTAT								as [Balança - Quantidade],
    KG_LIQUIDO								as [Balança - Peso Líquido],
    VL_FOB									as [Balança - Vl. FOB],
    VL_FRETE								as [Balança - Vl. Frete],
    VL_SEGURO								as [Balança - Vl. Seguro],
    ApplyMap('MAP_VIA', CO_VIA)				as [Balança - Via Modal],
    ApplyMap('MAP_URF', CO_URF)				as [Balança - URF Desc.]
FROM [lib://$(vStage)/IMP_COMPLETA.qvd] (qvd)
where CO_ANO >= 2017;



//==================================================================
Store BALANCA into [lib://$(vTransformados)/BALANCA.qvd](QVD);
Drop Table BALANCA;
//==================================================================