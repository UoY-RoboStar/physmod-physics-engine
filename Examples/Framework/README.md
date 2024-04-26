# Framework
![Framework](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/88e645d8-48e2-4ccb-b8ed-9f9be97680bf)

<details closed>
  <summary>We illustrate the steps of each technique applied to the following p-model:</summary>
    
  ![SimpleArmSerial](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/40aa0e10-6436-444d-aa79-88fe527a29ed)

  ![JointDefs](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/5f821b1f-1e85-43ef-bb0b-3795664cb316)


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

<details closed>
<summary>The result of this step is:</summary>

![Gripper](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/d022dd68-98ed-460e-af54-755f62de2b44)

![IntermediateLink](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/ecbaacd1-36e8-46ac-a486-b1cf2eab1098)

![BaseLink](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/9885871d-9d5a-4f6f-846c-342098f88ffe)

![WristJoint](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/1f3e7529-3fef-4a76-9e6e-6bf8a672bb42)

![ElbowJoint](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/53df0a07-9ece-4276-9384-fe3ae8064c64)

</details>




</details>

**Step 5)**
<details closed>

The formulation-dependent calculation for the whole system is as follows:

![SystemEquations](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/b6e45249-8a02-4e80-a488-93adf93540cd)

<details closed>
<summary>The result of this step is:</summary>
  
![pmodel1](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/ac0551b1-b9ae-4b2b-9d6d-b7b08f8b184b)

![pmodel2](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/905f693e-83e0-42d9-97b1-d1d83c1a5199)

![Functions](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/a253b328-da44-4b5d-9c32-92bf37f53c7e)


</details>


</details>

# Technique 4

![Technique4](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/321c62df-68ad-4902-9366-41bba2c3e1a0)

The input for this technique is:
<details closed>
pmodel = SimpleArm

userChoice = \{($\boldsymbol{\mathbf{\tau}}$, PlatformMapping, ($\boldsymbol{\mathbf{\tau}}$(0) = $\boldsymbol{\mathbf{0}}$, 1), (($\boldsymbol{\mathbf{\theta}}$,Method1, \textit{IBConditions}, 2)\}
</details>

**Step 1)**
<details closed>
  
![resolveMethod](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/b1a14b17-9287-4276-b151-7efb56ef3480)


<details closed>
<summary>The result of this step is:</summary>
  
choice = \{($\boldsymbol{\mathbf{\tau}}$, PlatformMapping, $\boldsymbol{\mathbf{\tau}}(0) = \boldsymbol{\mathbf{0}}$, 1), ($\boldsymbol{\mathbf{\theta}},Method1$, \textit{IBConditions}, 7), ($\dot{\boldsymbol{\mathbf{\theta}}}$, Euler, $\dot{\boldsymbol{\mathbf{\theta}}}(0) = \boldsymbol{\mathbf{0}}, 6)$, $(\ddot{\boldsymbol{\mathbf{\theta}}}$, Direct Forward Dynamics,  $\ddot{\boldsymbol{\mathbf{\theta}}}(0) = \\boldsymbol{\mathbf{0}}$, 5), ($\boldsymbol{\mathbf{C}}$, Newton-Euler Inverse Dynamics, $\boldsymbol{\mathbf{C}}(\boldsymbol{\mathbf{0}}) = \boldsymbol{\mathbf{0}}$, 3), ($\mathcal{M}$, Composite Body Algorithm, $\mathcal{M}(\boldsymbol{\mathbf{0}}) = \mathcal{M}$, 2), ($\mathcal{M}^{-1}$, Cholesky Algorithm, $\mathcal{M}^{-1}(\boldsymbol{\mathbf{0}}) = \boldsymbol{\mathbf{0}}$, 4)\}

</details>
</details>

**Step 2)**
<details closed>

![updatePModel](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/d57ea0e7-b3b5-472e-a886-8f0bf584f2e9)

<details closed>
  <summary>The result of this step:</summary>
  
  appends the variable minv to the pmodel. 
  </details>
</details>

**Step 3)**
<details closed>
<details closed>
<summary>The result of this step is:</summary>
  
![appendSolutions_result](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/a6d292e3-540f-4ecd-9682-d5a818b36be6)

  </details>
</details>

**Step 4)**
<details closed>

  The result of this step is:
<details closed>
  
![appendConstraints_result](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/19c71f53-2da1-406d-a6fa-53a62d6e47e1)

  </details>
</details>

**Step 5)**
<details closed>
  
<details closed>
<summary>The result of this step is:</summary>

![computeErrors_result](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/b7f99e80-7c75-4f71-b933-e7ec3d13995d)

  
  </details>
</details>

# Technique 5
![Technique5](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/251c93e0-ffdf-4b75-a85a-21505bfce027)



**Step 1)**
<details closed>
  
<details closed>
<summary>The result of this step is:</summary>

![GenerateSolutions1](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/f44d67b5-4de7-4cea-bada-3ddc46c95a1c)

![GenerateSolutions2](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/614e86b5-f3ef-4bb8-b908-2630e8cb4757)

![GenerateSolutions3](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/6aa5cc59-3ba8-487d-aada-c01bbb47a9ac)

  </details>
</details>

**Step 2)**
<details closed>
  
![initialiseState](https://github.com/UoY-RoboStar/physmod-physics-engine/assets/42748381/603035f5-2fa3-4f6e-aaf4-e8aa52e83696)

  The result of this step is:
<details closed>

  </details>
</details>

**Step 3)**
<details closed>

  The result of this step is:
<details closed>

  </details>
</details>

**Step 4)**
<details closed>

  The result of this step is:
<details closed>

  </details>
</details>
