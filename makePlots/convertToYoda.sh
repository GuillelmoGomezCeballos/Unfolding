#!/bin/bash
hadd masterMatrix.root matrix*root
root2yoda masterMatrix.root CMS_2018_PAS_SMP_17_010.yoda
sed -i 's$BEGIN YODA_SCATTER3D /$BEGIN YODA_SCATTER3D /REF/CMS_2018_PAS_SMP_17_010/$' CMS_2018_PAS_SMP_17_010.yoda
sed -i 's$Path=/$Path=/REF/CMS_2018_PAS_SMP_17_010/$' CMS_2018_PAS_SMP_17_010.yoda
sed '/^[0-9#]/d' CMS_2018_PAS_SMP_17_010.yoda > CMS_2018_PAS_SMP_17_010.plot