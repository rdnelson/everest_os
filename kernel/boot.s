%macro entry 1
  dd 0x00000083 + 0x1000 * %1
%endmacro


STACK_SIZE equ 0x4000
MBOOT_PAGE_ALIGN	equ 1<<0
MBOOT_MEM_INFO		equ 1<<1
MBOOT_HEADER_MAGIC	equ 0x1BADB002

MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

KERNEL_VBASE equ 0xC0000000
KERNEL_PAGE_NUM equ (KERNEL_VBASE >> 22)

[BITS 32]

[section .text]

mboot:
  dd  MBOOT_HEADER_MAGIC
  dd  MBOOT_HEADER_FLAGS
  dd  MBOOT_CHECKSUM

  dd  0
  dd  0
  dd  0
  dd  0
  dd  0

[GLOBAL kaslow]
[GLOBAL _kaslow]
[EXTERN kmain]

kaslow equ (_kaslow - KERNEL_VBASE)

_kaslow:
  cli
  mov ecx, (PAGE_TBL - KERNEL_VBASE)
  mov cr3, ecx

  mov ecx, cr0
  or ecx, 0x80000000
  mov cr0, ecx

  lea ecx, [_kasmain]
  jmp ecx

_kasmain:
;  mov dword [PAGE_TBL], 0
;  invlpg [0]

  sti
  mov esp, stack + STACK_SIZE

  add ebx, KERNEL_VBASE
  push	ebx

  call kmain
  jmp $
  add esp, 4


[section .data]

align 4096
PAGE_TBL:
  dd (0x00000083 + PAGE_DIR - KERNEL_VBASE)
  times (KERNEL_PAGE_NUM - 1) dd 0

  dd (0x00000083 + PAGE_DIR - KERNEL_VBASE)
  times (1024 - KERNEL_PAGE_NUM - 1) dd 0

align 4096
PAGE_DIR:
entry 0
entry 1
entry 2
entry 3
entry 4
entry 5
entry 6
entry 7
entry 8
entry 9
entry 10
entry 11
entry 12
entry 13
entry 14
entry 15
entry 16
entry 17
entry 18
entry 19
entry 20
entry 21
entry 22
entry 23
entry 24
entry 25
entry 26
entry 27
entry 28
entry 29
entry 30
entry 31
entry 32
entry 33
entry 34
entry 35
entry 36
entry 37
entry 38
entry 39
entry 40
entry 41
entry 42
entry 43
entry 44
entry 45
entry 46
entry 47
entry 48
entry 49
entry 50
entry 51
entry 52
entry 53
entry 54
entry 55
entry 56
entry 57
entry 58
entry 59
entry 60
entry 61
entry 62
entry 63
entry 64
entry 65
entry 66
entry 67
entry 68
entry 69
entry 70
entry 71
entry 72
entry 73
entry 74
entry 75
entry 76
entry 77
entry 78
entry 79
entry 80
entry 81
entry 82
entry 83
entry 84
entry 85
entry 86
entry 87
entry 88
entry 89
entry 90
entry 91
entry 92
entry 93
entry 94
entry 95
entry 96
entry 97
entry 98
entry 99
entry 100
entry 101
entry 102
entry 103
entry 104
entry 105
entry 106
entry 107
entry 108
entry 109
entry 110
entry 111
entry 112
entry 113
entry 114
entry 115
entry 116
entry 117
entry 118
entry 119
entry 120
entry 121
entry 122
entry 123
entry 124
entry 125
entry 126
entry 127
entry 128
entry 129
entry 130
entry 131
entry 132
entry 133
entry 134
entry 135
entry 136
entry 137
entry 138
entry 139
entry 140
entry 141
entry 142
entry 143
entry 144
entry 145
entry 146
entry 147
entry 148
entry 149
entry 150
entry 151
entry 152
entry 153
entry 154
entry 155
entry 156
entry 157
entry 158
entry 159
entry 160
entry 161
entry 162
entry 163
entry 164
entry 165
entry 166
entry 167
entry 168
entry 169
entry 170
entry 171
entry 172
entry 173
entry 174
entry 175
entry 176
entry 177
entry 178
entry 179
entry 180
entry 181
entry 182
entry 183
entry 184
entry 185
entry 186
entry 187
entry 188
entry 189
entry 190
entry 191
entry 192
entry 193
entry 194
entry 195
entry 196
entry 197
entry 198
entry 199
entry 200
entry 201
entry 202
entry 203
entry 204
entry 205
entry 206
entry 207
entry 208
entry 209
entry 210
entry 211
entry 212
entry 213
entry 214
entry 215
entry 216
entry 217
entry 218
entry 219
entry 220
entry 221
entry 222
entry 223
entry 224
entry 225
entry 226
entry 227
entry 228
entry 229
entry 230
entry 231
entry 232
entry 233
entry 234
entry 235
entry 236
entry 237
entry 238
entry 239
entry 240
entry 241
entry 242
entry 243
entry 244
entry 245
entry 246
entry 247
entry 248
entry 249
entry 250
entry 251
entry 252
entry 253
entry 254
entry 255
entry 256
entry 257
entry 258
entry 259
entry 260
entry 261
entry 262
entry 263
entry 264
entry 265
entry 266
entry 267
entry 268
entry 269
entry 270
entry 271
entry 272
entry 273
entry 274
entry 275
entry 276
entry 277
entry 278
entry 279
entry 280
entry 281
entry 282
entry 283
entry 284
entry 285
entry 286
entry 287
entry 288
entry 289
entry 290
entry 291
entry 292
entry 293
entry 294
entry 295
entry 296
entry 297
entry 298
entry 299
entry 300
entry 301
entry 302
entry 303
entry 304
entry 305
entry 306
entry 307
entry 308
entry 309
entry 310
entry 311
entry 312
entry 313
entry 314
entry 315
entry 316
entry 317
entry 318
entry 319
entry 320
entry 321
entry 322
entry 323
entry 324
entry 325
entry 326
entry 327
entry 328
entry 329
entry 330
entry 331
entry 332
entry 333
entry 334
entry 335
entry 336
entry 337
entry 338
entry 339
entry 340
entry 341
entry 342
entry 343
entry 344
entry 345
entry 346
entry 347
entry 348
entry 349
entry 350
entry 351
entry 352
entry 353
entry 354
entry 355
entry 356
entry 357
entry 358
entry 359
entry 360
entry 361
entry 362
entry 363
entry 364
entry 365
entry 366
entry 367
entry 368
entry 369
entry 370
entry 371
entry 372
entry 373
entry 374
entry 375
entry 376
entry 377
entry 378
entry 379
entry 380
entry 381
entry 382
entry 383
entry 384
entry 385
entry 386
entry 387
entry 388
entry 389
entry 390
entry 391
entry 392
entry 393
entry 394
entry 395
entry 396
entry 397
entry 398
entry 399
entry 400
entry 401
entry 402
entry 403
entry 404
entry 405
entry 406
entry 407
entry 408
entry 409
entry 410
entry 411
entry 412
entry 413
entry 414
entry 415
entry 416
entry 417
entry 418
entry 419
entry 420
entry 421
entry 422
entry 423
entry 424
entry 425
entry 426
entry 427
entry 428
entry 429
entry 430
entry 431
entry 432
entry 433
entry 434
entry 435
entry 436
entry 437
entry 438
entry 439
entry 440
entry 441
entry 442
entry 443
entry 444
entry 445
entry 446
entry 447
entry 448
entry 449
entry 450
entry 451
entry 452
entry 453
entry 454
entry 455
entry 456
entry 457
entry 458
entry 459
entry 460
entry 461
entry 462
entry 463
entry 464
entry 465
entry 466
entry 467
entry 468
entry 469
entry 470
entry 471
entry 472
entry 473
entry 474
entry 475
entry 476
entry 477
entry 478
entry 479
entry 480
entry 481
entry 482
entry 483
entry 484
entry 485
entry 486
entry 487
entry 488
entry 489
entry 490
entry 491
entry 492
entry 493
entry 494
entry 495
entry 496
entry 497
entry 498
entry 499
entry 500
entry 501
entry 502
entry 503
entry 504
entry 505
entry 506
entry 507
entry 508
entry 509
entry 510
entry 511
entry 512
entry 513
entry 514
entry 515
entry 516
entry 517
entry 518
entry 519
entry 520
entry 521
entry 522
entry 523
entry 524
entry 525
entry 526
entry 527
entry 528
entry 529
entry 530
entry 531
entry 532
entry 533
entry 534
entry 535
entry 536
entry 537
entry 538
entry 539
entry 540
entry 541
entry 542
entry 543
entry 544
entry 545
entry 546
entry 547
entry 548
entry 549
entry 550
entry 551
entry 552
entry 553
entry 554
entry 555
entry 556
entry 557
entry 558
entry 559
entry 560
entry 561
entry 562
entry 563
entry 564
entry 565
entry 566
entry 567
entry 568
entry 569
entry 570
entry 571
entry 572
entry 573
entry 574
entry 575
entry 576
entry 577
entry 578
entry 579
entry 580
entry 581
entry 582
entry 583
entry 584
entry 585
entry 586
entry 587
entry 588
entry 589
entry 590
entry 591
entry 592
entry 593
entry 594
entry 595
entry 596
entry 597
entry 598
entry 599
entry 600
entry 601
entry 602
entry 603
entry 604
entry 605
entry 606
entry 607
entry 608
entry 609
entry 610
entry 611
entry 612
entry 613
entry 614
entry 615
entry 616
entry 617
entry 618
entry 619
entry 620
entry 621
entry 622
entry 623
entry 624
entry 625
entry 626
entry 627
entry 628
entry 629
entry 630
entry 631
entry 632
entry 633
entry 634
entry 635
entry 636
entry 637
entry 638
entry 639
entry 640
entry 641
entry 642
entry 643
entry 644
entry 645
entry 646
entry 647
entry 648
entry 649
entry 650
entry 651
entry 652
entry 653
entry 654
entry 655
entry 656
entry 657
entry 658
entry 659
entry 660
entry 661
entry 662
entry 663
entry 664
entry 665
entry 666
entry 667
entry 668
entry 669
entry 670
entry 671
entry 672
entry 673
entry 674
entry 675
entry 676
entry 677
entry 678
entry 679
entry 680
entry 681
entry 682
entry 683
entry 684
entry 685
entry 686
entry 687
entry 688
entry 689
entry 690
entry 691
entry 692
entry 693
entry 694
entry 695
entry 696
entry 697
entry 698
entry 699
entry 700
entry 701
entry 702
entry 703
entry 704
entry 705
entry 706
entry 707
entry 708
entry 709
entry 710
entry 711
entry 712
entry 713
entry 714
entry 715
entry 716
entry 717
entry 718
entry 719
entry 720
entry 721
entry 722
entry 723
entry 724
entry 725
entry 726
entry 727
entry 728
entry 729
entry 730
entry 731
entry 732
entry 733
entry 734
entry 735
entry 736
entry 737
entry 738
entry 739
entry 740
entry 741
entry 742
entry 743
entry 744
entry 745
entry 746
entry 747
entry 748
entry 749
entry 750
entry 751
entry 752
entry 753
entry 754
entry 755
entry 756
entry 757
entry 758
entry 759
entry 760
entry 761
entry 762
entry 763
entry 764
entry 765
entry 766
entry 767
entry 768
entry 769
entry 770
entry 771
entry 772
entry 773
entry 774
entry 775
entry 776
entry 777
entry 778
entry 779
entry 780
entry 781
entry 782
entry 783
entry 784
entry 785
entry 786
entry 787
entry 788
entry 789
entry 790
entry 791
entry 792
entry 793
entry 794
entry 795
entry 796
entry 797
entry 798
entry 799
entry 800
entry 801
entry 802
entry 803
entry 804
entry 805
entry 806
entry 807
entry 808
entry 809
entry 810
entry 811
entry 812
entry 813
entry 814
entry 815
entry 816
entry 817
entry 818
entry 819
entry 820
entry 821
entry 822
entry 823
entry 824
entry 825
entry 826
entry 827
entry 828
entry 829
entry 830
entry 831
entry 832
entry 833
entry 834
entry 835
entry 836
entry 837
entry 838
entry 839
entry 840
entry 841
entry 842
entry 843
entry 844
entry 845
entry 846
entry 847
entry 848
entry 849
entry 850
entry 851
entry 852
entry 853
entry 854
entry 855
entry 856
entry 857
entry 858
entry 859
entry 860
entry 861
entry 862
entry 863
entry 864
entry 865
entry 866
entry 867
entry 868
entry 869
entry 870
entry 871
entry 872
entry 873
entry 874
entry 875
entry 876
entry 877
entry 878
entry 879
entry 880
entry 881
entry 882
entry 883
entry 884
entry 885
entry 886
entry 887
entry 888
entry 889
entry 890
entry 891
entry 892
entry 893
entry 894
entry 895
entry 896
entry 897
entry 898
entry 899
entry 900
entry 901
entry 902
entry 903
entry 904
entry 905
entry 906
entry 907
entry 908
entry 909
entry 910
entry 911
entry 912
entry 913
entry 914
entry 915
entry 916
entry 917
entry 918
entry 919
entry 920
entry 921
entry 922
entry 923
entry 924
entry 925
entry 926
entry 927
entry 928
entry 929
entry 930
entry 931
entry 932
entry 933
entry 934
entry 935
entry 936
entry 937
entry 938
entry 939
entry 940
entry 941
entry 942
entry 943
entry 944
entry 945
entry 946
entry 947
entry 948
entry 949
entry 950
entry 951
entry 952
entry 953
entry 954
entry 955
entry 956
entry 957
entry 958
entry 959
entry 960
entry 961
entry 962
entry 963
entry 964
entry 965
entry 966
entry 967
entry 968
entry 969
entry 970
entry 971
entry 972
entry 973
entry 974
entry 975
entry 976
entry 977
entry 978
entry 979
entry 980
entry 981
entry 982
entry 983
entry 984
entry 985
entry 986
entry 987
entry 988
entry 989
entry 990
entry 991
entry 992
entry 993
entry 994
entry 995
entry 996
entry 997
entry 998
entry 999
entry 1000
entry 1001
entry 1002
entry 1003
entry 1004
entry 1005
entry 1006
entry 1007
entry 1008
entry 1009
entry 1010
entry 1011
entry 1012
entry 1013
entry 1014
entry 1015
entry 1016
entry 1017
entry 1018
entry 1019
entry 1020
entry 1021
entry 1022
entry 1023

[section .bss]
align 32
stack:
   resb STACK_SIZE
