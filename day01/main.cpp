//
// Created by wuggy on 01/12/2017.
//

#include "day01.h"

#include <iostream>


const char * captcha =
  "2175234281493376693817212167497687911136241765326152235785581689365646244916837735928524481848972386998786124791228"
  "9729579296691684761143544956991583942215236568961875851755854977946147178746464675227699149925227227137557479769948"
  "5697888843993798211113825367226995757594744732739397563489927146679635961897657347431694895991257714433481933835661"
  "5984359354113474939256986548157835982584439445417321985791934934144214828222968954156116934162222235465139734292867"
  "8496478671339383923769856425795211323673389723181967933933832711545885653952861879231537976292517866354812943192728"
  "2632695247356984233366737351589938535561488338613279592622547566478277391452835777934815267681569211384283189393618"
  "5972177855626451964343587183574485924316722788956273871295365112831762467398521352589752237825917862541672215215572"
  "8615936587369515254936828668564857283226439881266871945998796488472249182538883354186573925183152663862683995449671"
  "6632857753974538762627225674524359147773635228175947419466389865717936558894664198959969241229157772244994814968373"
  "4319414912373535526815194171287124586355383695334988783194978886985292914784948926532584393466999939184628631926868"
  "6789372513976522282587526866148166337215961493536262851512218794139272361292811529888161198799297966893366553115353"
  "6392982567888193852724711872135791855235213416511179476767853411462354414114418132425148132278218438194246199749798"
  "8687164662191886527457453895176156785584568127236464613858471633359984383516737352524854754244294258312262453449444"
  "2516259616973235858469131159773167334953658673271599748942956981954699444528689628848694446818825465485122869742839"
  "7114711298626321286357796583657563628636271359836176133328497563719863769671175492515662819929645739296555893138719"
  "7655678484923191651383153825481234711625394981863352718517422156527977576674226268771311411434484353495883337263418"
  "2176866315441583887177759222598853735114191874277711434653854816841589229914164681364497429324463193669337827467661"
  "7738335178417637111563761476647491752672125623215677285757658448932327189714712898411716428689488521368186617412381"
  "78676857381583155547755219837116125995361896562498721571413742";

int main()
{
  std::cout << Day1::solve_part1(captcha) << std::endl;
  std::cout << Day1::solve_part2(captcha) << std::endl;

  return 0;
}