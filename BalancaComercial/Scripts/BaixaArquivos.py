'''
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
'''

import os
import requests
import zipfile

def baixar_arquivo(url, endereco):
    # faz requisição ao servidor
    resposta = requests.get(url)
    if resposta.status_code == requests.codes.OK:
        with open(endereco, 'wb') as novo_arquivo:
            novo_arquivo.write(resposta.content)
        print("Donwload finalizado. Salvo em: {}".format(endereco))
    else:
        resposta.raise_for_status()


def descompactaArquivo(ArqZip):
    with zipfile.ZipFile(ArqZip,"r") as Zip_ref:
        Zip_ref.extractall(OUTPUT_DIR)
    print("Extracao finalizada. Salvo em: {}".format(OUTPUT_DIR))

if __name__ == "__main__":
    #Exportacao
    BASE_EXP = 'https://balanca.economia.gov.br/balanca/bd/comexstat-bd/ncm/EXP_COMPLETA.zip'
    ARQ_EXP = 'EXP_COMPLETA.zip'
    
    #Importacao
    BASE_IMP = 'https://balanca.economia.gov.br/balanca/bd/comexstat-bd/ncm/IMP_COMPLETA.zip'
    ARQ_IMP = 'IMP_COMPLETA.zip'
    
    #Tabelas Auxiliares
    TAB_AUX = 'https://balanca.economia.gov.br/balanca/bd/tabelas/TABELAS_AUXILIARES.xlsx'
    ARQ_AUX = 'TABELAS_AUXILIARES.xlsx'

    OUTPUT_DIR = 'D:\\OneDrive\\Documentos\TesteUnimed\\Arquivos\\'
    for i in range(1,4):
        
        #Baixa o arquivo
        
        if i == 1:
            print('Baixando arquivo de Exportação')
            nome_arquivo = os.path.join(OUTPUT_DIR, ARQ_EXP)
            baixar_arquivo(BASE_EXP, nome_arquivo)
        elif i == 2:
            print('Baixando arquivo de Importação')
            nome_arquivo = os.path.join(OUTPUT_DIR, ARQ_IMP)
            baixar_arquivo(BASE_IMP, nome_arquivo)
        else:
            print('Baixando arquivo de Cadastros Auxiliares') 
            nome_arquivo = os.path.join(OUTPUT_DIR, ARQ_AUX)
            baixar_arquivo(TAB_AUX, nome_arquivo)

    #Descompacta os zip
    descompactaArquivo('D:\\OneDrive\\Documentos\TesteUnimed\\Arquivos\\IMP_COMPLETA.zip')
    descompactaArquivo('D:\\OneDrive\\Documentos\TesteUnimed\\Arquivos\\EXP_COMPLETA.zip')
