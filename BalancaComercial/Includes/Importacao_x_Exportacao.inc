/*
*******************************************************************
Aplicação.......: Extração de Dados de Importação/Exportação 
Desenvolvida por: Eduardo Dutka
Empresa.........: 
Criada em.......: 01/11/2021
Descrição.......: 
	
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
Set vTransformados    = 'Transformados';



//==================================================================
// Aba Balança Comercial
//==================================================================

//==================================================================
// Dados da Balança comercial (importação e exportação)
//==================================================================
[Balança]:
LOAD
    "Balança - Tipo",
    FLG_EXPORTACAO,
    "Balança - Ano",
    "Balança - Mês",
    "Balança - Periodo",
    [Balança - AnoMês],
    DATA,
    "NCM - Código",
    "Balança - Unidade",
    "País - Código",
    "UF - Sigla",
    "Via - Código",
    "URF - Código",
    "Balança - Quantidade",
    "Balança - Peso Líquido",
    "Balança - Vl. FOB",
    "Balança - Via Modal",
    "Balança - URF Desc.",
    "Balança - Vl. Frete",
    "Balança - Vl. Seguro"
FROM [lib://$(vTransformados)/Balanca.qvd](qvd);


//==================================================================
// Aba Cadastros
//==================================================================
//==================================================================
// Dados dos Países
//==================================================================
[PAIS]:
LOAD
    "País - Código",
    "País - Nome",
    "País - Bloco"
FROM [lib://$(vTransformados)/PAIS.qvd] (qvd);


//==================================================================
// Dados CUCI - Classificação Uniforme para Comércio Internacional
//==================================================================
[CUCI]:
LOAD
    "NCM - Código",
    "NCM - Nome",
    "Classif. - Desc. Item",
    "Classif. - Subclasse",
    "Classif. - Grupo",
    "Classif. - Divisão",
    "Classif. - Seção"
FROM [lib://$(vTransformados)/Classif_Uniforme_Com_Internacional.qvd](qvd);


//==================================================================
// Dados UF
//==================================================================
[UF]:
LOAD
    "UF - Código",
    "UF - Sigla",
    "UF - Nome",
    "UF - Região"
FROM [lib://$(vTransformados)/UF.qvd](qvd);



