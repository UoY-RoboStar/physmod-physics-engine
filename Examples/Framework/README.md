# Framework
![Framework](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/88e645d8-48e2-4ccb-b8ed-9f9be97680bf)

<details closed>
  <summary>We illustrate the steps of each technique applied to the following p-model:</summary>
    
  ![SimpleArmSerial](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/40aa0e10-6436-444d-aa79-88fe527a29ed)

</details>

# Technique 3
![Technique3](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/99aaf650-1751-4d50-a35b-245236da3117)

The result of each step of Technique 3 applied to the SimpleArm serial chain example is presented below.

**Step 1)**
<details closed>
    
  ![calculateFormulation](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/0a5a6903-476e-4a76-bc28-fcc4995b30fb)

  The result of this step is: formulation = _SKO_

</details>



**Step 2).**
<details closed>

![calculateTopology](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/a87bfaca-8e16-4e20-a2fe-39f07282f87d)

The output of this step is: Topology = _SerialChain_

</details>

**Step 3)**
<details closed>
  
![assignNumbering](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/929c841e-26af-44b2-becf-877ae8562476)

![orderPmodel](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/067685b1-74d6-4202-af9e-869591c98d46)

![getBaseLink](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/875c923a-064b-45d4-9fd7-877c679a6cb2)

![getChildLinks](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/c559cc30-e91d-4736-9540-124554900b1c)

The result of this step is: 

![assignNumberingOutput](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/c223e7a3-7483-46d8-be0c-48992fcd39e0)
</details>

**Step 4)**
<details closed>

The formulation-dependent calculation for the components is as follows:

![linkEquations](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/5aa0e785-7d58-43d9-a7c6-cb30edc276da)

![jointEquations](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/cb857dff-7273-4707-ac77-ae491bcb76b7)

The result of this step is:
<details closed>
  
![Gripper](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/1b91db98-1dc6-4631-8ee2-7cb74a984bc3)

![IntermediateLink](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/328b0f5e-d842-48bd-b95b-1f0bd4c0d72f)

![BaseLink](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/7b4633e8-3740-4d10-bc19-0488816ed6b5)

![WristJoint](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/d0d59e16-fce7-48f7-b9f6-b39cc5e1b2b2)

![ElbowJoint](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/cdd515d7-3dbc-4769-a48c-a406bff3c097)

</details>




</details>

**Step 5)**
<details closed>

The formulation-dependent calculation for the whole system is as follows:

![SystemEquations](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/b6e45249-8a02-4e80-a488-93adf93540cd)

The result of this step is:
<details closed>

![pmodel1](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/484d7a7f-2a08-4e8d-a1e6-87901eefb582)

![pmodel2](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/c8e5f629-f407-4807-b463-f1e243650dc6)

![Datatypes](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/23c4fa1e-1ebb-43fb-9c98-5508921aefe6)


</details>


</details>




# Technique 4

![Technique4](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/321c62df-68ad-4902-9366-41bba2c3e1a0)

The input for this technique is:
<details closed>
pmodel = SimpleArm

userChoice = \{($\bm{\tau}$, PlatformMapping, $\bm{\tau}(0) = \bm{0}$, 1), ($\bm{\theta},Method1$, \textit{IBConditions}, 7)\}
<\details>

**Step 1)**
<details closed>
![resolveMethod](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/b1a14b17-9287-4276-b151-7efb56ef3480)

<\details>

# Technique 5
![Technique5](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/251c93e0-ffdf-4b75-a85a-21505bfce027)

