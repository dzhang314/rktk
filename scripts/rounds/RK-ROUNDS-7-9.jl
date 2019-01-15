const ORDER = 7
const NUM_STAGES = 9
const NUM_VARS = 45
const NUM_CONSTRS = 85
const TABLE_SIZE = 506

const ROUNDS = [
    [
        (3, 9, 15, 1, -1), (4, 16, 23, 1, 1)
    ], [
        (5, 24, 29, 9, -1), (6, 30, 36, 16, -1), (7, 37, 43, 2, 9), (8, 44, 51, 1, 16), (15, 89, 95, 9, 9),
        (16, 96, 102, 9, 17), (17, 103, 110, 16, 16)
    ], [
        (9, 52, 56, 24, -1), (10, 57, 62, 30, -1), (11, 63, 68, 37, -1), (12, 69, 75, 44, -1), (13, 76, 81, 3, 24),
        (14, 82, 88, 2, 30), (24, 142, 147, 89, -1), (25, 148, 153, 96, -1), (26, 154, 160, 103, -1),
        (31, 185, 190, 10, 24), (32, 191, 197, 9, 30), (33, 198, 203, 18, 24), (34, 204, 210, 17, 30),
        (35, 211, 217, 2, 89), (36, 218, 224, 9, 45), (37, 225, 232, 1, 103), (75, 433, 438, 24, 24),
        (76, 439, 445, 30, 30), (77, 446, 451, 24, 31), (80, 465, 470, 24, 46), (81, 471, 477, 30, 45),
        (82, 478, 484, 9, 89), (83, 485, 491, 17, 89), (84, 492, 498, 9, 104), (85, 499, 506, 44, 44)
    ], [
        (18, 111, 114, 52, -1), (19, 115, 119, 57, -1), (20, 120, 124, 63, -1), (21, 125, 130, 69, -1),
        (22, 131, 135, 76, -1), (23, 136, 141, 82, -1), (27, 161, 165, 4, 52), (28, 166, 171, 3, 57),
        (29, 172, 177, 3, 63), (30, 178, 184, 2, 69), (44, 258, 262, 142, -1), (45, 263, 267, 148, -1),
        (46, 268, 273, 154, -1), (51, 294, 298, 185, -1), (52, 299, 304, 191, -1), (53, 305, 309, 198, -1),
        (54, 310, 315, 204, -1), (55, 316, 321, 211, -1), (56, 322, 327, 218, -1), (57, 328, 334, 225, -1),
        (64, 366, 371, 3, 142), (65, 372, 377, 3, 148), (66, 378, 384, 2, 154), (67, 385, 389, 11, 52),
        (68, 390, 395, 10, 57), (69, 396, 401, 10, 63), (70, 402, 408, 9, 69), (71, 409, 413, 19, 52),
        (72, 414, 419, 18, 57), (73, 420, 425, 18, 63), (74, 426, 432, 17, 69), (78, 452, 457, 3, 185),
        (79, 458, 464, 2, 191)
    ], [
        (38, 233, 235, 111, -1), (39, 236, 239, 115, -1), (40, 240, 243, 120, -1), (41, 244, 248, 125, -1),
        (42, 249, 252, 131, -1), (43, 253, 257, 136, -1), (47, 274, 277, 161, -1), (48, 278, 282, 166, -1),
        (49, 283, 287, 172, -1), (50, 288, 293, 178, -1), (58, 335, 338, 5, 111), (59, 339, 343, 4, 115),
        (60, 344, 348, 4, 120), (61, 349, 354, 3, 125), (62, 355, 359, 4, 131), (63, 360, 365, 3, 136)
    ]
]
